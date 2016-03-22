#include "dataset.h"

#include <cstring>

using VarPro::Dataset;

Dataset::Dataset(){

}

Dataset::~Dataset(){

}

const double* Dataset::GetTimestamps(){
  return timestamps_;
}

void Dataset::SetTimeStamps(double* timestamps, int length){
  timestamps_ = timestamps;
  number_of_timestamps = length;
}

const double* Dataset::GetWavelenghts(){
  return wavelengths_
}

void Dataset::SetWavelengths(double* wavelengths, int length){
  wavelengths_ = wavelengths;
  number_of_wavelengths = length;
}

double** Dataset::GetObservations(){
  return observations_;
}

void Dataset::SetObservations(double** observations, int* num_rows, int num_cols){
  observations_ = observations;
  number_of_observation_rows = num_rows;
  number_of_observation_cols = num_cols;
}

double* Dataset::GetIRFVector(){
  return irfvec_;
}

void Dataset::SetIRFVector(double* irfvec, int length){
  irfvec_ = irfvec;
  number_of_irf_parameters = length;
}

double* Dataset::GetRateConstants(){
  return rateconstants_;
}

void Dataset::SetRateConstants(double* rateconstants, int length){
  rateconstants_ = rateconstants;
  number_of_rateconstants = length;
}

int Dataset::GetNumberOfTimestamps() const{
  return number_of_timestamps;
}

int Dataset::GetNumberOfWavelenghts() const{
  return number_of_wavelengths;
}

void Dataset::GetSizeOfObservations(int** num_rows, int* num_cols){
  *num_rows = number_of_observation_rows;
  *num_cols = number_of_observation_cols;
}

int Dataset::GetNumberOfRateconstants() const{
  return number_of_rateconstants;
}

int Dataset::GetNumberOfIRFParameters() const{
 return number_of_irf_parameters;
}
