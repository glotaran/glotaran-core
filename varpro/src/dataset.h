#ifndef DATASET_H
#define DATASET_H

namespace VarPro{
  
  class Dataset{
  public:
    Dataset();
    ~Dataset();
    
    double* GetTimestamps();
    void SetTimeStamps(double* timestamps, int length);
    
    double* GetWavelenghts();
    void SetWavelengths(double* wavelengths, int length);
    
    double* GetObservations();
    void SetObservations(double* observations, int num_rows, int num_cols);
    
    double* GetRateConstants(bool for_simulation=false);
    void SetRateConstants(double* rateconstants, int length, bool for_simulation=false);
    
    double* GetIRFVector();
    void SetIRFVector(double* irfvec, int length);
    
    double* GetLocations();
    void SetLocations(double* location, int length);
    
    double* GetDelta();
    void SetDelta(double* delta, int length);
    
    double* GetAmp();
    void SetAmp(double* amp, int length);
    
    int GetNumberOfTimestamps() const;
    int GetNumberOfWavelenghts() const;
    void GetSizeOfObservations(int* num_rows, int* num_cols);
    int GetNumberOfRateconstants(bool for_simulation=false) const;
    int GetNumberOfIRFParameters() const;
    int GetNumberOfLocationFactors() const;
    int GetNumberOfDeltaFactors() const;
    int GetNumberOfAmplificationFactors() const;
      
  private:
    double* timestamps_;
    int number_of_timestamps;
    
    double* wavelengths_;
    int number_of_wavelengths;
    
    double* observations_;
    int number_of_observation_rows;
    int number_of_observation_cols;
    
    double* rateconstants_[2];
    int number_of_rateconstants[2];
    
    double* irfvec_;
    int number_of_irf_parameters;
    
    double* location_;
    int number_of_location_factors;
    
    double* delta_;
    int number_of_delta_factors;
    
    double* amp_;
    int number_of_amplification_factors;
  };
}

#endif // DATASET_H
