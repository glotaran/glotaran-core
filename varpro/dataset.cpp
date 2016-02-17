#include "dataset.h"

#include <iostream>
#include <fstream>

#include <mili.h>
#include <mili/stream_utils.h>

Dataset::Dataset(){

}

Dataset::Dataset(std::vector<std::vector<double>>& data){
  ParseFromVectorField(data);
}

Dataset::Dataset(Vector& timestamps, Vector& wavelengths, ColMajorMatrix& observations) : 
timestamps_(timestamps), wavelengths_(wavelengths), observations_(observations){
 
}


Dataset::Dataset(std::string& file_name){
  std::ifstream in(file_name);
  ParseFromStream(in);
  in.close();
}

Dataset::~Dataset(){
  
}

void Dataset::ParseFromSingleVectors(std::vector<double>& timestamps, std::vector<double>& wavelengths, std::vector<std::vector<double>>& observations){
  timestamps_(timestamps.size());
  wavelengths_(wavelengths.size());
  observations_((observations.size()), (observations.at(0).size()));
  
  for(int i = 0; i < timestamps.size(); ++i){
    timestamps_[i] = timestamps.at(i);
  }
  
  for(int i = 0; i < wavelengths.size(); ++i){
    wavelengths_[i] = wavelengths.at(i);
  }
  
  for(int i = 1; i < observations.size(); ++i){
    for(int j = 1; j < observations.at(i).size(); ++j){
      observations_(i, j) = observations.at(i).at(j); 
    }
  }
  
}
//TODO test later
void Dataset::ParseFromVectorField(std::vector<std::vector<double>>& data){
  timestamps_(data.size() - 1);
  wavelengths_(data.at(0).size());
  observations_((data.size() - 1), (data.at(0).size() - 1));
  
  for(int i = 0; i < data.at(0).size(); ++i){
    wavelengths_[i] = data.at(0).at(i);
  }
  
  for(int i = 1; i < data.size(); ++i){
    timestamps_[i] = data.at(i).at(0);
    for(int j = 1; j < data.at(i).size(); ++j){
      observations_((i - 1), (j - 1)) = data.at(i).at(j); 
    }
  }
}
//TODO test later
void Dataset::ParseFromStream(std::istream& in){
  std::vector<std::vector<double>> data;
  std::vector<double> d;
  
  /*while(in >> d){
    data.push_back(d);
    d.clear();
  }*/
  
  ParseFromVectorField(data);

}

const Vector& Dataset::GetTimestamps(){
  return timestamps_;
}

const Vector& Dataset::GetWavelenghts(){
  return wavelengths_;
}

const ColMajorMatrix& Dataset::GetObservations(){
  return observations_;
}

Vector& Dataset::GetRateConstants(){
  return rateconstants_;
}
    
void Dataset::SetRateConstants(Vector& rateconstants){
  rateconstants_ = rateconstants;
}
    
int Dataset::GetNumberOfTimestamps() const{
  return timestamps_.size();
}

int Dataset::GetNumberOfWavelenghts() const{
  return wavelengths_.size();
}
    
int Dataset::GetNumberOfRateconstants() const{
  return rateconstants_.size();
}

std::ostream& operator<<(std::ostream& out, Dataset& dataset){
  out << "Timestamps: " << dataset.GetTimestamps() << std:: endl;
  out << "Wavelengths: " << dataset.GetWavelenghts() << std::endl;
  out << "Observations: " << dataset.GetObservations() << std::endl;
  return out;
}

std::istream& operator>>(std::istream& in, Dataset& dataset){
  dataset.ParseFromStream(in);
  return in;
}