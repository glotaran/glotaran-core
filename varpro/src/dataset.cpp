#include "dataset.h"

#include <iostream>
#include <fstream>

Dataset::Dataset(){

}

Dataset::~Dataset(){
  
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

const double* Dataset::GetObservations()
{
  return observations_.data();
}

void Dataset::SetObservations(double* observations, int num_rows, int num_cols, bool copy)
{
  ColMajorMatrix o = Eigen::Map<Eigen::MatrixXd>(observations, num_rows, num_cols);
  if(copy)
    observations_ = ColMajorMatrix(o);
  else
    observations_ = o;
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

std::pair<int, int> Dataset::GetSizeOfObservations()
{
  return std::make_pair<int, int>(observations_.rows(), observations_.cols());
}

void Dataset::GetSizeOfObservations(int* num_rows, int* num_cols)
{
  *num_rows = observations_.rows();
  *num_cols = observations_.cols();
}

int Dataset::GetNumberOfRateconstants() const{
  return rateconstants_.size();
}

