#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "analysis-core/plugin/simulatorplugin.h"
#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

namespace AnalysisCore{
  class Simulator{
    
  public:
    static bool Simulate(const std::shared_ptr<SimulatorPlugin>& plugin, const std::shared_ptr<Dataset>& dataset, const std::shared_ptr<Options>& options);
  };
}
#endif // SIMULATOR_H
