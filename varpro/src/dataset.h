#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Core>
#include <ceres/ceres.h>

using ceres::Vector;
using ceres::ColMajorMatrix;
namespace VarPro{
  
  class Dataset{
  public:
    Dataset();
    ~Dataset();
    
    const double* GetTimestamps();
    void SetTimeStamps(double* timestamps, int length, bool copy=false);
    
    const double* GetWavelenghts();
    void SetWavelengths(double* wavelengths, int length, bool copy=false);
    
    double** GetObservations();
    void SetObservations(double** observations, int* num_rows, int num_cols, bool copy=false);
    
    double* GetIRFVector();
    void SetIRFVector(double* irfvec, int length, bool copy=false);
    
    double* GetRateConstants();
    void SetRateConstants(double* rateconstants, int length, bool copy=false);
    
    int GetNumberOfTimestamps() const;
    int GetNumberOfWavelenghts() const;
    void GetSizeOfObservations(int** num_rows, int* num_cols);
    int GetNumberOfRateconstants() const;
    
      
      
  private:
    Vector timestamps_;
    Vector wavelengths_;
    double** observations_;
    Vector rateconstants_;
    Vector irfvec_;
    
    int* number_of_observation_rows;
    int number_of_observation_cols;
  };
}

#endif // DATASET_H
