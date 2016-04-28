#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "analysis-core/api.h"

static double* regspace(double start, double delta, double end, int* number){
  int M = (int)floor((end - start) / delta);
  double* space = malloc(sizeof(double) * (M + 1));
  int i = 0;
  for(; i <= M; ++i)
    space[i] = start + i * delta;
  *number = M;
  return space;
}

int main(int argc, char** argv) {
  int number_of_timestamps;
  double* times = regspace(0, 1.5, 1500, &number_of_timestamps);
  
  int number_of_wavelengths;
  double* wavenum = regspace(12820, 4.6, 15120, &number_of_wavelengths);
  
  int number_of_locations = 6;
  double location[] = {14705, 13513, 14492, 14388, 14184, 13986};
  
  int number_of_deltas = 6;
  double delta[] = {400, 1000, 300, 200, 350, 330};
  
  int number_of_amps = 6;
  double amp[] = {1, 0.2, 1, 1, 1, 1};
  
  int number_of_rate_constants = 6;
  double kinpar[] = {.006667, .006667, 0.00333, 0.00035, 0.0303, 0.000909};
  
  int i;
  
  core_t* c;
  
  int id;
  void* dataset;
  void* datasets[1];
  
  void* options;
  
  c = ac_init();
  
  ac_create_dataset(c, &dataset, &id);
  
  ac_create_options(c, &options);
  //ac_options_set_bool(options, "noise", true);
  
  ac_dataset_set_vector(dataset, "times", times, number_of_timestamps);
  ac_dataset_set_vector(dataset, "wavenum", wavenum, number_of_wavelengths);
  ac_dataset_set_vector(dataset, "location", location, number_of_locations);
  ac_dataset_set_vector(dataset, "delta", delta, number_of_deltas);
  ac_dataset_set_vector(dataset, "amp", amp, number_of_amps);
  ac_dataset_set_vector(dataset, "kinpar", kinpar, number_of_rate_constants);
  
  ac_simulate_using_plugin_with_dataset(c, "kin_sim", dataset, options);
  
  number_of_rate_constants = 5;
  double k[] = {.005, 0.003, 0.00022, 0.0300, 0.000888};
  
  ac_dataset_set_vector(dataset, "kinpar", kinpar, number_of_rate_constants);
  
  datasets[0] = dataset;
  
  ac_solve_using_plugin_with_datasets(c, "kin_sol", datasets, 1, options);
  
  double* k_solved = ac_dataset_get_vector(dataset, "kinpar", &number_of_rate_constants);
  
  for(i = 0; i < number_of_rate_constants; ++i)
    printf("%f\n", k_solved[i]);

  ac_free(c);
  
  return 0;
}