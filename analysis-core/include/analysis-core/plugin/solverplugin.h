#ifndef SOLVER_PLUGIN_H
#define SOLVER_PLUGIN_H

#include <map>
#include <memory>
#include <utility>

#include <ceres/problem.h>

#include "analysis-core_export.h"

#include "analysis-core/plugin/plugin.h"

#include "analysis-core/dataset.h"

namespace AnalysisCore{
  
  class ANALYSIS_CORE_EXPORT SolverPlugin : public Plugin{
    
  public:
    
    class ANALYSIS_CORE_EXPORT SolverFunctor : public virtual Functor{
    public:
      virtual ~SolverFunctor(){}
      virtual bool operator()(double const* const* parameters, double* residuals) const = 0;
      
      inline void AddDataset(int id, std::shared_ptr<Dataset> dataset){
        datasets_[id] = dataset;
      }
      
      inline std::shared_ptr<Dataset> GetDataset(int id){
        return datasets_[id];
      }
      
      inline void SetWavelength(int wavelength){
        wavelength_ = wavelength;
      }
           
    protected:
      int wavelength_;
      std::map<int, std::shared_ptr<Dataset>> datasets_;
    };
       
    virtual ~SolverPlugin(){}
        
    virtual void FillProblem(ceres::Problem& problem, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options) = 0;
    
    virtual SolverFunctor* CreateSolverFunctor() = 0;
    
  };
  
}

#endif //SOLVER_PLUGIN_H