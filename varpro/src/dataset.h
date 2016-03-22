#ifndef DATASET_H
#define DATASET_H

namespace VarPro{
  
  class Dataset{
  public:
    Dataset();
    ~Dataset();
    
    const double* GetTimestamps();
    void SetTimeStamps(double* timestamps, int length);
    
    const double* GetWavelenghts();
    void SetWavelengths(double* wavelengths, int length);
    
    double** GetObservations();
    void SetObservations(double** observations, int* num_rows, int num_cols);
    
    double* GetIRFVector();
    void SetIRFVector(double* irfvec, int length);
    
    double* GetRateConstants();
    void SetRateConstants(double* rateconstants, int length);
    
    int GetNumberOfTimestamps() const;
    int GetNumberOfWavelenghts() const;
    void GetSizeOfObservations(int** num_rows, int* num_cols);
    int GetNumberOfRateconstants() const;
    int GetNumberOfIRFParameters() const;
    
      
      
  private:
    double* timestamps_;
    int number_of_timestamps;
    
    double* wavelengths_;
    int number_of_wavelengths;
    
    double** observations_;
    int* number_of_observation_rows;
    int number_of_observation_cols;
    
    double* rateconstants_;
    int number_of_rateconstants;
    
    double* irfvec_;
    int number_of_irf_parameters;
    
  };
}

#endif // DATASET_H
