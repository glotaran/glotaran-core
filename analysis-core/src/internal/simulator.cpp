#include "analysis-core/internal/simulator.h"

using namespace AnalysisCore;

bool Simulator::Simulate(const std::shared_ptr<SimulatorPlugin>& plugin, const std::shared_ptr<Dataset>& dataset, const std::shared_ptr<Options>& options){
  auto functor = plugin->CreateSimulatorFunctor();
  
  functor->SetDataset(dataset);
  functor->SetOptions(options);
  
  return (*functor)();
}

