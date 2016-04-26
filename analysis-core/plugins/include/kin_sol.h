#ifndef KIN_SOL_H
#define KIN_SOL_H

#include "analysis-core_export.h"

#include "analysis-core/plugin/solverplugin.h"

namespace AnalysisCore{
  
  class ANALYSIS_CORE_EXPORT KinSolPlugin : public SolverPlugin{
    
  public:
    
    class KinSolFunctor : public SolverFunctor{
    public:
      KinSolFunctor();
      virtual ~KinSolFunctor();
      
      mat&& CalculateC(double const* const* parameters);
      
      bool operator()(double const* const* parameters, double* residuals) const;
    };
    
    KinSolPlugin();
    virtual ~KinSolPlugin();
    
    std::string Name() const;
    
    void FillProblem(ceres::Problem& problem, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options);
    
    SolverFunctor* CreateSolverFunctor();
    
  };
  
}

#endif //KIN_SOL_H