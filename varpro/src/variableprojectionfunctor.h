#ifndef VARIABLEPROJECTIONFUNCTOR_H
#define VARIABLEPROJECTIONFUNCTOR_H

#include <ceres/ceres.h>

#include "dataset.h"
#include "options.h"

using ceres::ColMajorMatrix;
namespace VarPro{
  
  class VariableProjectionFunctor
  {
  public:
    VariableProjectionFunctor(Dataset* dataset, Options* options);
    virtual ~VariableProjectionFunctor();
    
    virtual bool operator()(double const* const* parameters, double* residuals) const = 0;
    virtual Dataset operator()() = 0;
    
    
  protected:
    Dataset* dataset_;
    Options* options_;
    
    virtual ColMajorMatrix calcC() = 0;
  };

}
#endif // VARIABLEPROJECTIONFUNCTOR_H
