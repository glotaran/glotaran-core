#ifndef KIN_SIM_H
#define KIN_SIM_H

#include "analysis-core_export.h"

#include "analysis-core/plugin/simulatorplugin.h"

namespace AnalysisCore{
  
  class ANALYSIS_CORE_EXPORT KinSimPlugin : public SimulatorPlugin{
    
  public:
    
    class KinSimFunctor : public SimulatorFunctor{
    public:
      KinSimFunctor();
      virtual ~KinSimFunctor();
      
      mat&& CalculateC(double const* const* parameters = nullptr);
      
      bool operator()();
    };
    
    KinSimPlugin();
    virtual ~KinSimPlugin();
    
    std::string Name() const;
    
    SimulatorFunctor* CreateSimulatorFunctor();
  };
  
}

#endif //KIN_SIM_H