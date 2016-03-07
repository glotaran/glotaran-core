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
    
    const Vector& GetTimestamps();
    const Vector& GetWavelenghts();
    const ColMajorMatrix& GetObservations();
    const Vector& GetIRFVector();
    
    Vector& GetRateConstants();
    void SetRateConstants(Vector& rateconstants);
    void SetIRFVector(Vector& irfvec);
    
    int GetNumberOfTimestamps() const;
    int GetNumberOfWavelenghts() const;
    int GetNumberOfRateconstants() const;
    
    
private:
  Vector timestamps_;
  Vector wavelengths_;
  ColMajorMatrix observations_;
  Vector rateconstants_;
  Vector irfvec_;
};

std::ostream& operator<<(std::ostream& out, Dataset& dataset);
std::istream& operator>>(std::istream& in, Dataset& dataset);

#endif // DATASET_H
