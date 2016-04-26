#include "analysis-core/internal/base.h"
#include "analysis-core/options.h"

using namespace AnalysisCore;

Options::Options(){
  ceres_options_.max_num_iterations = 25;
  ceres_options_.linear_solver_type = ceres::DENSE_QR;
  ceres_options_.minimizer_progress_to_stdout = true;
  ceres_options_.num_threads = 8;
  ceres_options_.gradient_tolerance = 1e-30;
  ceres_options_.function_tolerance = 1e-30;
  ceres_options_.parameter_tolerance = 1e-30;
}

std::shared_ptr<Options>&& Options::Create(){
  return std::move(std::make_shared<Options>());
}

Options::~Options(){

}

ceres::Solver::Options& Options::GetCeresOptions(){
  return ceres_options_;
}

void Options::SetCeresOptions(ceres::Solver::Options& ceres_options){
  ceres_options_ = ceres_options;
}

ANALYSIS_CORE_EXPORT bool ac_options_get_bool(void* options, const char* member_name){
  return ac_get_bool(options, member_name);
}

ANALYSIS_CORE_EXPORT double ac_options_get_double(void* options, const char* member_name){
  return ac_get_double(options, member_name);
}

ANALYSIS_CORE_EXPORT int ac_options_get_int(void* options, const char* member_name){
  return ac_get_int(options, member_name);
}

ANALYSIS_CORE_EXPORT const char* ac_options_get_string(void* options, const char* member_name){
  return ac_get_string(options, member_name);
}

ANALYSIS_CORE_EXPORT void* ac_options_get_arbitrary(void* options, const char* member_name){
  return ac_get_arbitrary(options, member_name);
}

ANALYSIS_CORE_EXPORT double* ac_options_get_vector(void* options, const char* member_name, int* num_rows){
  return ac_get_vector(options, member_name, num_rows);
}

ANALYSIS_CORE_EXPORT double* ac_options_get_matrix(void* options, const char* member_name, int* num_rows, int* num_cols){
  return ac_get_matrix(options, member_name, num_rows, num_cols);
}

ANALYSIS_CORE_EXPORT void ac_options_set_bool(void* options, const char* member_name, bool value){
  ac_set_bool(options, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_options_set_double(void* options, const char* member_name, double value){
  ac_set_double(options, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_options_set_int(void* options, const char* member_name, int value){
  ac_set_int(options, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_options_set_string(void* options, const char* member_name, const char* value){
  ac_set_string(options, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_options_set_arbitrary(void* options, const char* member_name, void* value){
  ac_set_arbitrary(options, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_options_set_vector(void* options, const char* member_name, double* vector, int num_rows){
  ac_set_vector(options, member_name, vector, num_rows);
}

ANALYSIS_CORE_EXPORT void ac_options_set_matrix(void* options, const char* member_name, double* matrix, int num_rows, int num_cols){
  ac_set_matrix(options, member_name, matrix, num_rows, num_cols);
}