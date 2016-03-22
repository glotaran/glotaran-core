#include "simulator.h"

using namespace VarPro;

Simulator::Simulator(Dataset* dataset, Options* options, VariableProjectionFunctor* functor) :
  dataset_(dataset), options_(options), functor_(functor)
{

}

Simulator::~Simulator()
{

}

Dataset Simulator::Evaluate()
{
  return functor_->operator()();
}
