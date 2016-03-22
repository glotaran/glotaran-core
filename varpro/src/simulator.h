#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <ceres/ceres.h>

#include "dataset.h"
#include "options.h"

#include "variableprojectionfunctor.h"

/*using ceres::Vector;
using ceres::internal::scoped_ptr;

template <typename ModelFunctor>
class Simulator
{
public:
Simulator(Vector& times, Vector& wavenum, Vector& irfvec, Vector& location, Vector& delta, Vector& amp, Vector& kinpar, ModelFunctor* functor) : 
times_(times), wavenum_(wavenum), irfvec_(irfvec), location_(location), delta_(delta), amp_(amp), kinpar_(kinpar), functor_(functor){

}

~Simulator(){
  
}

Dataset Evaluate(){
    return (*functor_)(times_, wavenum_, irfvec_, location_, delta_, amp_, kinpar_);
}

private:
  Vector& times_;
  Vector& wavenum_;
  Vector& irfvec_;
  Vector& location_;
  Vector& delta_;
  Vector& amp_;
  Vector& kinpar_;
  scoped_ptr<ModelFunctor> functor_;
  
  Dataset dataset_;
  
};*/

namespace VarPro{

  class Simulator{
  public:
    Simulator(Dataset* dataset, Options* options, VariableProjectionFunctor* functor);
    ~Simulator();
    
    Dataset Evaluate();
    
  private:
    Dataset* dataset_;
    Options* options_;
    VariableProjectionFunctor* functor_;
  };
    
}

#endif // SIMULATOR_H
