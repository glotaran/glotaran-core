#include "kin_sol.h"

#include <ceres/dynamic_numeric_diff_cost_function.h>

#include "internal/lapack.h"


using namespace AnalysisCore;

KinSolPlugin::KinSolFunctor::KinSolFunctor(){

}

KinSolPlugin::KinSolFunctor::~KinSolFunctor(){

}

mat KinSolPlugin::KinSolFunctor::CalculateC(double const* const* parameters){
  auto dataset = (*datasets_.begin()).second;
  const vec& T = dataset->Get<vec>("times").value_or(vec());
  int number_of_rateconstants;
  double* kinpar = dataset->Get<vec, double*>("kinpar", &number_of_rateconstants);
  vec k = vec(parameters[0], number_of_rateconstants);
  mat C = exp(T * -k.t());
  return C;
}

bool KinSolPlugin::KinSolFunctor::operator()(double const* const* parameters, double* residuals) const {
    
    auto dataset = (*datasets_.begin()).second;
    
    mat C = const_cast<KinSolFunctor*>(this)->CalculateC(parameters);

    auto PSI = dataset->Get<mat>("PSI").value_or(mat());
    
    if(PSI.n_elem == 0)
      return false;
    
    vec b = PSI.col(wavelength_);
    
    LAPACK::GetResidualsUsingQR(C.n_rows, C.n_cols, b.n_rows, b.n_cols, C.memptr(), b.memptr());
    
    for(int i = 0; i < C.n_rows; ++i)
      residuals[i] = b[i];
    
    return true;
}

KinSolPlugin::KinSolPlugin(){

}

KinSolPlugin::~KinSolPlugin(){

}

std::string KinSolPlugin::Name() const {
  return "kin_sol";
}

void KinSolPlugin::FillProblem(ceres::Problem& problem, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options){
  auto dataset = datasets.at(0);
  
  int number_of_timestamps;
  int number_of_wavelengths;
  int number_of_rateconstants;
  
  double* timestamps = dataset->Get<vec, double*>("times", &number_of_timestamps);
  double* wavelengths = dataset->Get<vec, double*>("wavenum", &number_of_wavelengths);
  double* rateconstants = dataset->Get<vec, double*>("kinpar", &number_of_rateconstants);
  
  for(int i = 0; i < number_of_wavelengths; ++i){
    auto functor = CreateSolverFunctor();
    functor->AddDataset(dataset->GetId(), dataset);
    functor->SetWavelength(i);
    ceres::DynamicNumericDiffCostFunction<SolverFunctor>* costFunction = new ceres::DynamicNumericDiffCostFunction<SolverFunctor>(functor);
    costFunction->AddParameterBlock(number_of_rateconstants);
    costFunction->SetNumResiduals(number_of_timestamps);
    problem.AddResidualBlock(costFunction, NULL, rateconstants);
  }
}

SolverPlugin::SolverFunctor* KinSolPlugin::CreateSolverFunctor(){
  return new KinSolFunctor();
}
