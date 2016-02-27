// Author: yaminokeshin@gmail.com (Stefan Schütz)

#include <cstring>

#include "ceres/ceres.h"
#include "ceres/numeric_diff_cost_function.h"
#include "glog/logging.h"
#include "eigen3/Eigen/Dense"
#include <Eigen/Core>

#include "dataset.h"
#include "simulator.h"
#include "lapack.h"

using namespace Eigen;
using namespace ceres;

// Starting values: 0.01 0.05 0.08 and initial cost: 6.943527
//  It.   1, fac=           1, eval (no.,total): ( 1,  1): new dev = 1.16756
//1.167563 :  0.003852691 0.061744326 0.091428342
//  It.   2, fac=           1, eval (no.,total): ( 1,  2): new dev = 0.384246
//0.3842463 :  0.004938872 0.049614922 0.088766865
//  It.   3, fac=           1, eval (no.,total): ( 1,  3): new dev = 0.380239
//0.3802389 :  0.005039473 0.049692617 0.089345688
//  It.   4, fac=           1, eval (no.,total): ( 1,  4): new dev = 0.380239
//0.3802389 :  0.005039668 0.049696966 0.089352916
//
// ### Parameter estimates ###
// 
//
//Sum square error: 0.3802389 
//
//Residual standard error: 0.009957391 on 3835 degrees
//    of freedom
//
//
//Parameters: kinpar 
//dataset 1: 0.00503966786236027, 0.0496969656191525, 0.0893529159322471
//    standard errors: 1.62787800156254e-05, 0.00039216731393182, 0.000449611960993873


struct ExponentialResidual{
  ExponentialResidual(int l, Dataset& dataset) : 
   l_(l), dataset_(dataset){}
  
  template <typename T> bool operator()(T const* const* parameters,
                                        T* residuals) const {
    
    int lt = dataset_.GetNumberOfTimestamps();
    ColMajorMatrix C = ExponentialResidual::CompModel(parameters[0], dataset_);
    Vector res = ExponentialResidual::CompResiduals(l_, C, dataset_);
    for(int i = 0; i < lt; i++)
      residuals[i] = res[i];//, 0);
    
    return true;
    
  }
  
private:
  
  static ColMajorMatrix CompModel(const double* k, const Dataset& dataset){
    Dataset& d = const_cast<Dataset&>(dataset);
    const int lt = d.GetNumberOfTimestamps();
    const int lk = d.GetNumberOfRateconstants();
    const Vector& T = d.GetTimestamps();
    ColMajorMatrix C(lt, lk);
    for(int i = 0; i < lt; ++i){
      for(int j = 0; j < lk; ++j){
        C(i, j) = ceres::exp(-k[j] * T[i]);
      }
    }
    return C;
  }
  
  static Vector CompResiduals(const int l, const ColMajorMatrix& C, const Dataset& dataset){
    Dataset& d = const_cast<Dataset&>(dataset);
    const int lk = d.GetNumberOfRateconstants();
    ColMajorMatrix psi = d.GetObservations();

    Vector b = psi.col(l);
    
    LAPACK::GetResidualsUsingQR(C.rows(), C.cols(), b.rows(), b.cols(), C.data(), b.data());
    
    return b;
        
  }
  
  const int l_;
  const Dataset dataset_;
};

struct ModelFunctor{
  Dataset operator()(Vector& times, Vector& wavenum, Vector& irfvec, Vector& location, Vector& delta, Vector& amp, Vector& kinpar){
    //std::cout << delta << std::endl;
    ColMajorMatrix E(wavenum.size(), location.size());
    for(int i = 0; i < location.size(); ++i){
      Vector loc(wavenum.size());
      loc.setConstant(location[i]);
      Vector tmp = 2 * (wavenum - loc) / delta[i]; //Needs a better name
      //std::cout << tmp << std::endl;
      for(int j = 0; j < tmp.size(); ++j)
        tmp[j] = tmp[j] * tmp[j];
      Vector tmp2 = -ceres::log(2) * tmp;
      //std::cout << tmp2 << std::endl;
      for(int j = 0; j < tmp2.size(); ++j)
        tmp2[j] = ceres::exp(tmp2[j]);
      //std::cout << tmp2 << std::endl;
      E.col(i) = amp[i] * tmp2;
    }
    ColMajorMatrix C = ModelFunctor::CompModel(kinpar, times, kinpar.size(), times.size());
    ColMajorMatrix PSI = C * E.transpose();
    //std::cout << PSI << std::endl;
    Dataset dataset(times, wavenum, PSI);
    return dataset;
  }
  
  static ColMajorMatrix CompModel(const Vector& k, const Vector& T, const int lk, const int lt){
    ceres::Matrix C(lt, lk);
    for(int i = 0; i < lt; ++i){
      for(int j = 0; j < lk; ++j){
        C(i, j) = ceres::exp(-k[j] * T[i]);
      }
    }
    return C;
  }
};

Vector Range(double lower, double upper, double step_size = 1.0){
  int size =(int) ((upper - lower) / step_size) + 1;
  Vector result(size);
  int i = 0;
  while (abs(upper - lower) > 1e-6){
    result[i] = lower;
    ++i;
    lower += step_size;
  }
  result[i] = lower;
  return result;
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  Vector times = Range(0, 300, 7.5);
  Vector wavenum = Range(18000, 28000, 100);
  Vector irfvec;
  Vector location(3);
  location << 26000, 23000, 20000;
  Vector delta(3);
  delta << 2000, 3000, 4000;
  Vector amp(3);
  amp << 1, 2, 3;
  Vector kinpar(3);
  kinpar << .01, .05, .09;
  ModelFunctor* functor = new ModelFunctor();
  Simulator<ModelFunctor> simulator(times, wavenum, irfvec, location, delta, amp, kinpar, functor);
  Dataset dataset = simulator.Evaluate();
  Vector k(3);
  k << 0.01, 0.05, 0.08;
  dataset.SetRateConstants(k);
  //double k[3] = {0.01, 0.05, 0.08};
  Problem problem;
   
  for(int i = 0; i < dataset.GetNumberOfWavelenghts(); ++i){
    DynamicNumericDiffCostFunction<ExponentialResidual>* costFunction = new DynamicNumericDiffCostFunction<ExponentialResidual>(
      new ExponentialResidual(i, dataset));
    costFunction->AddParameterBlock(dataset.GetNumberOfRateconstants());
    costFunction->SetNumResiduals(dataset.GetNumberOfTimestamps());
    problem.AddResidualBlock(costFunction, NULL, k.data());
  }
  
  Solver::Options options;
  options.max_num_iterations = 25;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  options.num_threads = 8;

  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.FullReport() << std::endl;
  std::cout << k[0] << " " << k[1] << " " << k[2] << std::endl;
  
  return 0;
}