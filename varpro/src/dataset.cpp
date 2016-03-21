#include "dataset.h"

#include <iostream>
#include <fstream>

Dataset::Dataset(){

}

Dataset::~Dataset(){
  delete number_of_observation_rows;
}

const double* Dataset::GetTimestamps()
{
  return timestamps_.data();
}

void Dataset::SetTimeStamps(double* timestamps, int length, bool copy)
{
  Vector t = Eigen::Map<Eigen::VectorXd>(timestamps, length);
  if(copy)
    timestamps_ = Vector(t);
  else
    timestamps_ = t;
}

const double* Dataset::GetWavelenghts()
{
  return wavelengths_.data();
}

void Dataset::SetWavelengths(double* wavelengths, int length, bool copy)
{
  Vector w = Eigen::Map<Eigen::VectorXd>(wavelengths, length);
  if(copy)
    wavelengths_ = Vector(w);
  else
    wavelengths_ = w;
}

double** Dataset::GetObservations()
{
  return observations_;
}

void Dataset::SetObservations(double** observations, int* num_rows, int num_cols, bool copy)
{
  if(copy){
    observations_ = new double*[num_cols];
    for(int i = 0; i < num_cols; ++i){
      observations_[i] = new double[num_rows[i]];
      for(int j = 0; j < num_rows[i]; ++j)
        observations_[i][j]=observations[i][j];
    }
  }
  else
    observations_ = observations;
  
  number_of_observation_rows = new int[num_cols];
  
  for(int i = 0; i < num_cols; ++i)
    number_of_observation_rows[i] = num_rows[i];
  
  number_of_observation_cols = num_cols;
  
}

double* Dataset::GetIRFVector()
{
  return irfvec_.data();
}

void Dataset::SetIRFVector(double* irfvec, int length, bool copy)
{
  Vector i = Eigen::Map<Eigen::VectorXd>(irfvec, length);
  if(copy)
    irfvec_ = Vector(i);
  else
    irfvec_ = i;
}

double* Dataset::GetRateConstants()
{
  return rateconstants_.data();
}

void Dataset::SetRateConstants(double* rateconstants, int length, bool copy)
{
  Vector r = Eigen::Map<Eigen::VectorXd>(rateconstants, length);
  if(copy)
    rateconstants_ = Vector(r);
  else
    rateconstants_ = r;
}

int Dataset::GetNumberOfTimestamps() const{
  return timestamps_.size();
}

int Dataset::GetNumberOfWavelenghts() const{
  return wavelengths_.size();
}

void Dataset::GetSizeOfObservations(int** num_rows, int* num_cols)
{
  *num_rows = number_of_observation_rows;
  *num_cols = number_of_observation_cols;
}

int Dataset::GetNumberOfRateconstants() const{
  return rateconstants_.size();
}

