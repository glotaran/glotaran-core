#include "kin_sim.h"

using namespace AnalysisCore;

KinSimPlugin::KinSimFunctor::KinSimFunctor(){

}

KinSimPlugin::KinSimFunctor::~KinSimFunctor(){

}

bool KinSimPlugin::KinSimFunctor::operator()(){
  auto C = CalculateC();
  auto E = CalculateE();
  
  mat PSI = C * E.t();
  
  bool noise = options_->Get<bool>("noise").value_or(false);
  double sigma = options_->Get<double>("sigma").value_or(0.005);
  double seed = options_->Get<double>("seed").value_or(123.0);
  
  if(noise){
    arma_rng::set_seed(seed);
    PSI += (sigma * mat(PSI.n_rows, PSI.n_cols, fill::randn));
  }
  
  dataset_->Set<mat>("PSI", PSI);
  
  return true;
}

mat KinSimPlugin::KinSimFunctor::CalculateC(double const* const* parameters){
  vec T = dataset_->Get<vec>("times").value_or(vec());
  vec k = dataset_->Get<vec>("kinpar").value_or(vec());
  mat C = exp(T * -k.t());
  return C;
}

KinSimPlugin::KinSimPlugin(){

}

KinSimPlugin::~KinSimPlugin(){

}

std::string KinSimPlugin::Name() const {
  return "kin_sim";
}

SimulatorPlugin::SimulatorFunctor* KinSimPlugin::CreateSimulatorFunctor() {
  return new KinSimFunctor();
}
