#include "variableprojectionfunctor.h"

using namespace VarPro;
using ceres::Vector;

VariableProjectionFunctor::VariableProjectionFunctor(int id, Dataset* dataset, Options* options) :
  id_(id), dataset_(dataset), options_(options){

}

VariableProjectionFunctor::~VariableProjectionFunctor(){

}

double* VariableProjectionFunctor::calcE()
{
    double* times = dataset_->GetTimestamps();
    double* wavenum = dataset_->GetWavelenghts();
    double* location = dataset_->GetLocations();
    double* delta = dataset_->GetDelta();
    double* amp = dataset_->GetAmp();
    double* kinpar = dataset_->GetRateConstants();
    
    int lt = dataset_->GetNumberOfTimestamps();
    int lw = dataset_->GetNumberOfWavelenghts();
    int ll = dataset_->GetNumberOfLocationFactors();
    int lk = dataset_->GetNumberOfRateconstants();
    
    double* E = new double[lw * ll];
    Eigen::Map<Eigen::MatrixXd> mapped_E(E, lw, ll);
    
    for(int i = 0; i < ll; ++i){
      Vector loc(lw);
      loc.setConstant(location[i]);
      Eigen::Map<Eigen::VectorXd> w(wavenum, lw);
      Vector tmp = 2 * (w - loc) / delta[i]; //Needs a better name
      for(int j = 0; j < tmp.size(); ++j)
        tmp[j] = tmp[j] * tmp[j];
      Vector tmp2 = -ceres::log(2) * tmp;
      for(int j = 0; j < tmp2.size(); ++j)
        tmp2[j] = ceres::exp(tmp2[j]);
      mapped_E.col(i) = amp[i] * tmp2;
    }
    
    return E;
}
