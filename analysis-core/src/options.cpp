#include "analysis-core/internal/base.h"
#include "analysis-core/options.h"

using namespace AnalysisCore;

Options::Options(){
  ceres_options_.max_num_iterations = 25;
  ceres_options_.linear_solver_type = ceres::DENSE_QR;
#ifndef NDEBUG
  ceres_options_.minimizer_progress_to_stdout = true;
#else
  ceres_options_.minimizer_progress_to_stdout = false;
#endif
  ceres_options_.num_threads = 8;
  ceres_options_.gradient_tolerance = 1e-30;
  ceres_options_.function_tolerance = 1e-30;
  ceres_options_.parameter_tolerance = 1e-30;
}

std::shared_ptr<Options> Options::Create(){
  return std::make_shared<Options>();
}

Options::~Options(){

}

ceres::Solver::Options& Options::GetCeresOptions(){
  return ceres_options_;
}

void Options::SetCeresOptions(ceres::Solver::Options& ceres_options){
  ceres_options_ = ceres_options;
}