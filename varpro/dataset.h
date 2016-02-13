#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Core>
#include <ceres/ceres.h>

using ceres::Vector;
using ceres::ColMajorMatrix;

class Dataset{
  public:
    Dataset();
    Dataset(int number_of_rateconstants);
    Dataset(Vector& timestamps, Vector& wavelengths, ColMajorMatrix& observations);
    Dataset(std::vector<std::vector<double>>& data);
    Dataset(std::string& file_name);
    
    ~Dataset();
    
    void ParseFromSingleVectors(std::vector<double>& timestamps, std::vector<double>& wavelengths, std::vector<std::vector<double>>& observations);
    void ParseFromVectorField(std::vector<std::vector<double>>& data);
    void ParseFromStream(std::istream& in);
    
    Vector& GetTimestamps() const;
    Vector& GetWavelenghts() const;
    ColMajorMatrix& GetObservations() const;
    
    int GetNumberOfRateconstants() const;
    void SetNumberOfRateconstants(int number_of_rateconstants);
    
private:
  Vector timestamps_;
  Vector wavelengths_;
  ColMajorMatrix observations_;
    
  int number_of_timestamps_;
  int number_of_wavelengths_;
  int number_of_rateconstants_;
};

std::ostream& operator<<(std::ostream& out, const Dataset& dataset);
std::istream& operator>>(std::istream& in, Dataset& dataset);

#endif // DATASET_H
