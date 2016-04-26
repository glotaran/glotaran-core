#ifndef PLUGIN_H
#define PLUGIN_H

#include <memory>
#include <map>

#include <armadillo>

#include "analysis-core_export.h"

#include "analysis-core/options.h"

using namespace arma;

namespace AnalysisCore{
  
  class ANALYSIS_CORE_EXPORT Plugin{
    
  public:
    
    class Functor{
    public:
      virtual ~Functor();
      virtual mat&& CalculateC(double const* const* parameters) = 0;
      
      inline void SetOptions(std::shared_ptr<Options> options){
        options_ = options;
      }
      
    protected:
      std::shared_ptr<Options> options_;
    };
    
    virtual ~Plugin();
    virtual std::string Name() const = 0;
    
  };
  
}

#endif //PLUGIN_H