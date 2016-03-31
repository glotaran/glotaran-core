// Author: yaminokeshin@gmail.com (Stefan Schütz)

/*#include <algorithm>
#include <cstring>
#include <random>

#include "ceres/ceres.h"
#include "ceres/numeric_diff_cost_function.h"
#include "glog/logging.h"
#include "eigen3/Eigen/Dense"
#include <Eigen/Core>

#include "dataset.h"
#include "simulator.h"
#include "lapack.h"

extern "C" void calcCirf(double *cmat, double *k, double *x, double *tau, double *mu,
              int *lenk, int *lenx);

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
    
    Dataset& d = const_cast<Dataset&>(dataset_);
    int lt = d.GetNumberOfTimestamps();
    
    ColMajorMatrix C;
    if(d.GetIRFVector().size() == 0)
      C = ExponentialResidual::CalcC(parameters[0], dataset_);
    else
      C = ExponentialResidual::CalcCirf(parameters[0], dataset_);
    
    const ColMajorMatrix& psi = d.GetObservations();
    Vector b = psi.col(l_);
    
    Vector res = ExponentialResidual::CompResiduals(b, C, dataset_);
    for(int i = 0; i < lt; i++)
      residuals[i] = res[i];
    
    return true;
    
  }
  
private:
  
  static ColMajorMatrix CalcC(const double* k, const Dataset& dataset){
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
  
  static ColMajorMatrix CalcCirf(const double* k, const Dataset& dataset){
    Dataset& d = const_cast<Dataset&>(dataset);
    int lt = d.GetNumberOfTimestamps();
    int lk = d.GetNumberOfRateconstants();
    const Vector& T = d.GetTimestamps();
    double mu = d.GetIRFVector()[0];
    double tau = d.GetIRFVector()[1];
    ColMajorMatrix C(lt, lk);
    double* mutable_k = const_cast<double*>(k);
    Vector& mutable_T = const_cast<Vector&>(T);
    
    calcCirf(C.data(), mutable_k, mutable_T.data(), &tau, &mu, &lk, &lt);
    return C;
  }
  
  static Vector CompResiduals(const Vector& b, const ColMajorMatrix& C, const Dataset& dataset){   
    LAPACK::GetResidualsUsingQR(C.rows(), C.cols(), b.rows(), b.cols(), C.data(), b.data());
    return b;
  }
  
  const int l_;
  const Dataset dataset_;
};

struct ModelFunctor{
  ModelFunctor(bool noise=false) : 
  noise_(noise){}
  
  Dataset operator()(Vector& times, Vector& wavenum, Vector& irfvec, Vector& location, Vector& delta, Vector& amp, Vector& kinpar){
    ColMajorMatrix E(wavenum.size(), location.size());
    
    std::mt19937 gen(123.0);
    std::normal_distribution<double> d;
    
    for(int i = 0; i < location.size(); ++i){
      Vector loc(wavenum.size());
      loc.setConstant(location[i]);
      Vector tmp = 2 * (wavenum - loc) / delta[i]; //Needs a better name
      for(int j = 0; j < tmp.size(); ++j)
        tmp[j] = tmp[j] * tmp[j];
      Vector tmp2 = -ceres::log(2) * tmp;
      for(int j = 0; j < tmp2.size(); ++j)
        tmp2[j] = ceres::exp(tmp2[j]);
      E.col(i) = amp[i] * tmp2;
    }
    ColMajorMatrix C;
    if(irfvec.size() == 0)
      C = ModelFunctor::CalcC(kinpar, times);
    else
      C = ModelFunctor::CalcCirf(kinpar, times, irfvec);
    ColMajorMatrix PSI = C * E.transpose();
    
    
    if(noise_){
      for(int i = 0; i < PSI.rows(); ++i){
        for(int j = 0; j < PSI.cols(); ++j){
          PSI(i, j) += 0.005 * d(gen);
        }
      }
    }
    
    Dataset dataset(times, wavenum, PSI);
    return dataset;
  }
  
  static ColMajorMatrix CalcC(const Vector& k, const Vector& T){
    int lk = k.size();
    int lt = T.size();
    ColMajorMatrix C(lt, lk);
    for(int i = 0; i < lt; ++i){
      for(int j = 0; j < lk; ++j){
        C(i, j) = ceres::exp(-k[j] * T[i]);
      }
    }
    return C;
  }
  
  static ColMajorMatrix CalcCirf(const Vector& k, const Vector& T, const Vector& irfvec){
    int lk = k.size();
    int lt = T.size();
    double mu = irfvec[0];
    double tau = irfvec[1];
    ColMajorMatrix C(lt, lk);
    Vector& mutable_k = const_cast<Vector&>(k);
    Vector& mutable_T = const_cast<Vector&>(T);
    calcCirf(C.data(), mutable_k.data(), mutable_T.data(), &tau, &mu, &lk, &lt);
    return C;
  }
  
private:
  bool noise_;
  
};*/

#include <algorithm>
#include <cstring>

#include "ceres/ceres.h"

#include "varpro.h"

using namespace ceres;
using namespace VarPro;

class LargeExampleFunctor : public VariableProjectionFunctor {
public:
  LargeExampleFunctor(int id, Dataset* dataset, Options* options):
    VariableProjectionFunctor(id, dataset, options){
  }
  
  ~LargeExampleFunctor(){
    
  }
  
  bool operator()(double const* const* parameters, double* residuals) const{
    int lt = dataset_->GetNumberOfTimestamps();
    int lw = dataset_->GetNumberOfWavelenghts();
    int lk = dataset_->GetNumberOfRateconstants();
    
    double* C = const_cast<LargeExampleFunctor*>(this)->calcC(parameters, false);
    
    double* PSI = dataset_->GetObservations();
    Eigen::Map<Eigen::MatrixXd> mapped_PSI(PSI, lt, lw);
    
    Vector b = mapped_PSI.col(id_);
    LAPACK::GetResidualsUsingQR(lt, lk, lt, 1, C, b.data());
    
    for(int i = 0; i < lt; ++i)
      residuals[i] = b[i];
    
    return true;
  }
  
  bool operator()(){
    double** parameters = new double*[1];
    parameters[0] = dataset_->GetRateConstants(true);
    
    double* C = calcC(parameters, true);
    double* E = calcE();
    
    int lt = dataset_->GetNumberOfTimestamps();
    int lw = dataset_->GetNumberOfWavelenghts();
    int ll = dataset_->GetNumberOfLocationFactors();
    int lk = dataset_->GetNumberOfRateconstants(true);
    
    Eigen::Map<Eigen::MatrixXd> mapped_C(C, lt, lk);
    Eigen::Map<Eigen::MatrixXd> mapped_E(E, lw, ll);
    
    double* PSI = new double[lt * lw];
    Eigen::Map<Eigen::MatrixXd> mapped_PSI(PSI, lt, lw);
    
    mapped_PSI = mapped_C * mapped_E.transpose();
    
    dataset_->SetObservations(PSI, lt, lw);
    
    delete[] parameters;
    delete[] C;
    delete[] E;
    
    return true;
  }
  
  int l_;

private:
  double* calcC(double const* const* parameters, bool for_simulation){
    double* T = dataset_->GetTimestamps();
    const double* k = parameters[0];
    int lt = dataset_->GetNumberOfTimestamps();
    int lk = dataset_->GetNumberOfRateconstants(for_simulation);
    double* C = new double[lt * lk];
    Eigen::Map<Eigen::MatrixXd> mapped_C(C, lt, lk);
    for(int i = 0; i < lt; ++i){
      for(int j = 0; j < lk; ++j){
        mapped_C(i, j) = ceres::exp(-k[j] * T[i]);
      }
    }
    return C;
  }
  
};

Vector Range(double lower, double upper, double step_size = 1.0){
  int size =(int) ((upper - lower) / step_size) + 1;
  Vector result(size);
  std::generate(result.data(), result.data() + size, [&lower, &step_size]{return lower += step_size;});
  return result;
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  
  Vector times1 = Range(-0.5, 9.98, 0.02);
  Vector times2 = Range(10, 1500, 3.0);
  Vector times(times1.size() + times2.size());
  times << times1, times2;
  Vector wavenum = Range(12820, 15120, 4.6);
  Vector irfvec(2);
  irfvec << -0.02, 0.05;
  Vector location(6);
  location << 14705, 13513, 14492, 14388, 14184, 13986;
  Vector delta(6);
  delta << 400, 1000, 300, 200, 350, 330;
  Vector amp(6);
  amp << 1, 0.2, 1, 1, 1, 1;
  Vector kinpar(6);
  kinpar << .006667, .006667, 0.00333, 0.00035, 0.0303, 0.000909;
  
  Options o;
  o.simulate = true;
  o.simulate_noise = false;
  o.irf = false;
  
  Dataset dataset;
  dataset.SetTimeStamps(times.data(), times.size());
  dataset.SetWavelengths(wavenum.data(), wavenum.size());
  dataset.SetLocations(location.data(), location.size());
  dataset.SetDelta(delta.data(), delta.size());
  dataset.SetAmp(amp.data(), amp.size());
  dataset.SetRateConstants(kinpar.data(), kinpar.size(), true);
  
  LargeExampleFunctor functor(0, &dataset, &o);
  
  Simulator simulator(&dataset, &o, &functor);
  
  simulator.Evaluate();
  
  Vector k(5);
  k << .005, 0.003, 0.00022, 0.0300, 0.000888;
  dataset.SetRateConstants(k.data(), 5);
  
  Problem problem;
   
  for(int i = 0; i < dataset.GetNumberOfWavelenghts(); ++i){
    DynamicNumericDiffCostFunction<LargeExampleFunctor>* costFunction = new DynamicNumericDiffCostFunction<LargeExampleFunctor>(
      new LargeExampleFunctor(i, &dataset, &o));
    costFunction->AddParameterBlock(dataset.GetNumberOfRateconstants());
    costFunction->SetNumResiduals(dataset.GetNumberOfTimestamps());
    problem.AddResidualBlock(costFunction, NULL, dataset.GetRateConstants());
  }
  
  Solver::Options options;
  options.max_num_iterations = 25;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  options.num_threads = 8;
  options.gradient_tolerance = 1e-30;
  options.function_tolerance = 1e-30;
  options.parameter_tolerance = 1e-30;
  

  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.FullReport() << std::endl;
  
  std::cout << k << std::endl;
    
  return 0;
}