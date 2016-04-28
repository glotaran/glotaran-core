
#include <iostream>
#include <iomanip>

#include <armadillo>

#include "analysis-core/core.h"
#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

using namespace AnalysisCore;
using namespace arma;

int main(int argc, char** argv) {
  vec times = regspace(0, 1.5, 1500);
  vec wavenum = regspace(12820, 4.6, 15120);
  vec location({14705, 13513, 14492, 14388, 14184, 13986});
  vec delta({400, 1000, 300, 200, 350, 330});
  vec amp({1, 0.2, 1, 1, 1, 1});
  vec kinpar({.006667, .006667, 0.00333, 0.00035, 0.0303, 0.000909});
  
  Core c;
  
  auto ds = c.CreateDataset();
  auto dataset = ds.first;
  auto id = ds.second;
  
  auto options = c.CreateOptions();
  
  //options->Set<bool>("noise", true);
  
  dataset->Set<vec>("times", times);
  dataset->Set<vec>("wavenum", wavenum);
  dataset->Set<vec>("location", location);
  dataset->Set<vec>("delta", delta);
  dataset->Set<vec>("amp", amp);
  dataset->Set<vec>("kinpar", kinpar);
  
  c.SimulateUsingPlugin("kin_sim", dataset, options);
    
  vec k({.005, 0.003, 0.00022, 0.0300, 0.000888});
  dataset->Set<vec>("kinpar", k);
  
  c.SolveUsingPlugin("kin_sol", {dataset}, options);
  
  vec k_solved = dataset->Get<vec>("kinpar").value_or(vec());
  std::cout << std::setprecision(10);
  k_solved.raw_print(std::cout);
  return 0;
}