#include "kin_sol.h"

#include <ceres/dynamic_numeric_diff_cost_function.h>

#include "internal/lapack.h"


using namespace AnalysisCore;

KinSolPlugin::KinSolFunctor::KinSolFunctor(){

}

KinSolPlugin::KinSolFunctor::~KinSolFunctor(){

}

mat&& KinSolPlugin::KinSolFunctor::CalculateC(double const* const* parameters){
  auto dataset = (*datasets_.begin()).second;
  const vec& T = dataset->Get<vec>("times").value_or(vec());
  const vec& kinpar = dataset->Get<vec>("kinpar").value_or(vec());
  vec k = vec(parameters[0], kinpar.n_rows);
  mat C = exp(T * k.t());
  return std::move(C);
}

bool KinSolPlugin::KinSolFunctor::operator()(double const* const* parameters, double* residuals) const {
    
    auto dataset = (*datasets_.begin()).second;
    
    const vec& timestamps = dataset->Get<vec>("times").value_or(vec());
    const vec& rateconstants = dataset->Get<vec>("kinpar").value_or(vec());
    
    auto C = const_cast<KinSolFunctor*>(this)->CalculateC(parameters);
    
    auto PSI = dataset->Get<mat>("PSI").value_or(mat());
        
    if(PSI.n_elem == 0)
      return false;
    
    vec b = PSI.col(wavelength_);
    
    LAPACK::GetResidualsUsingQR(timestamps.n_rows, rateconstants.n_rows, timestamps.n_rows, 1, C.memptr(), b.memptr());
    
    for(int i = 0; i < timestamps.n_rows; ++i)
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
  const vec& timestamps = dataset->Get<vec>("times").value_or(vec());
  const vec& wavelengths = dataset->Get<vec>("wavenum").value_or(vec());
  vec rateconstants = dataset->Get<vec>("kinpar").value_or(vec());
  
  for(int i = 0; i < wavelengths.n_rows; ++i){
    auto functor = CreateSolverFunctor();
    functor->AddDataset(dataset->GetId(), dataset);
    functor->SetWavelength(i);
    ceres::DynamicNumericDiffCostFunction<SolverFunctor>* costFunction = new ceres::DynamicNumericDiffCostFunction<SolverFunctor>(functor);
    costFunction->AddParameterBlock(rateconstants.n_rows);
    costFunction->SetNumResiduals(timestamps.n_rows);
    problem.AddResidualBlock(costFunction, NULL, rateconstants.memptr());
  }
  
  dataset->Set<vec>("kinpar", rateconstants);
}

SolverPlugin::SolverFunctor* KinSolPlugin::CreateSolverFunctor(){
  return new KinSolFunctor();
}
