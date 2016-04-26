#ifndef SIMULATOR_PLUGIN_H
#define SIMULATOR_PLUGIN_H

#include <memory>

#include "analysis-core_export.h"

#include "analysis-core/plugin/plugin.h"

#include "analysis-core/dataset.h"

namespace AnalysisCore{
  
  class ANALYSIS_CORE_EXPORT SimulatorPlugin : public virtual Plugin{
    
  public:
    
    class SimulatorFunctor : public virtual Functor{
    public:
      virtual ~SimulatorFunctor();
      virtual bool operator()() = 0;
      
      inline void SetDataset(std::shared_ptr<Dataset> dataset){
        dataset_ = dataset;
      }
      
      inline std::shared_ptr<Dataset> GetDataset(){
        return dataset_;
      }
      
      inline mat&& CalculateE(){      
        const vec& location = dataset_->Get<vec>("location").value_or(vec());
        const vec& delta = dataset_->Get<vec>("delta").value_or(vec());
        const vec& amp = dataset_->Get<vec>("amp").value_or(vec());
        const vec& wavenum = dataset_->Get<vec>("wavenum").value_or(vec());
        
        mat E(wavenum.n_rows, location.n_rows);
        
        int i = 0;
                
        E.each_row([&](rowvec& v){
          rowvec r = 2 * (wavenum.t() - rowvec(wavenum.n_cols, fill::ones) * location[i]) / delta[i];
          r.for_each([](mat::elem_type& val){val *= val;});
          v = amp[i] * exp(-log(2) * r);
          ++i;
        });
       
        return std::move(E);
      }
      
    protected:
      std::shared_ptr<Dataset> dataset_;
    };
    
    virtual SimulatorFunctor* CreateSimulatorFunctor() = 0;
    
  };
  
}

#endif //SIMULATOR_PLUGIN_H