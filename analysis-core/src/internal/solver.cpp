#include "analysis-core/internal/solver.h"

#include <ceres/solver.h>

#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

#include "analysis-core/plugin/solverplugin.h"

using namespace AnalysisCore;

bool Solver::Solve(const std::shared_ptr<SolverPlugin>& plugin, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options){
  ceres::Solver::Options& ceres_options = options->GetCeresOptions();
  ceres::Problem problem;
  
  plugin->FillProblem(problem, datasets, options);
  
  ceres::Solver::Summary summary;
  ceres::Solve(ceres_options, &problem, &summary);
  
  return true;
}
