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
    VariableProjectionFunctor(int id, Dataset* dataset, Options* options);
    virtual ~VariableProjectionFunctor();
    
    virtual bool operator()(double const* const* parameters, double* residuals) const = 0;
    virtual bool operator()() = 0;
    
    
  protected:
    int id_;
    Dataset* dataset_;
    Options* options_;
    
    virtual double* calcC(double const* const* parameters) = 0;
    double* calcE();
  };

}
#endif // VARIABLEPROJECTIONFUNCTOR_H
