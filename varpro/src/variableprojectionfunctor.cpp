#include "variableprojectionfunctor.h"

using VarPro::VariableProjectionFunctor;

VariableProjectionFunctor::VariableProjectionFunctor(Dataset* dataset, Options* options) :
  dataset_(dataset), options_(options)
{

}

VariableProjectionFunctor::~VariableProjectionFunctor()
{

}
