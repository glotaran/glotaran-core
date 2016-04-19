#include <memory>

#include "analysis-core/internal/base.h"
#include "analysis-core/dataset.h"

using namespace AnalysisCore;

Dataset::Dataset(int id) : id_(id){

}

Dataset::~Dataset(){

}

std::shared_ptr<MemberBase> Dataset::Get(const std::string& name)
{
  return members_[name];
}

ANALYSIS_CORE_EXPORT bool ac_dataset_get_bool(void* dataset, const char* member_name){
  return ac_get_bool(dataset, member_name);
}

ANALYSIS_CORE_EXPORT double ac_dataset_get_double(void* dataset, const char* member_name){
  return ac_get_double(dataset, member_name);
}

ANALYSIS_CORE_EXPORT const char* ac_dataset_get_string(void* dataset, const char* member_name){
  return ac_get_string(dataset, member_name);
}

ANALYSIS_CORE_EXPORT double* ac_dataset_get_vector(void* dataset, const char* member_name, int* num_rows){
  return ac_get_vector(dataset, member_name, num_rows);
}

ANALYSIS_CORE_EXPORT double* ac_dataset_get_matrix(void* dataset, const char* member_name, int* num_rows, int* num_cols){
  return ac_get_matrix(dataset, member_name, num_rows, num_cols);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_bool(void* dataset, const char* member_name, bool value){
  ac_set_bool(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_double(void* dataset, const char* member_name, double value){
  ac_set_double(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_string(void* dataset, const char* member_name, const char* value){
  ac_set_string(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_vector(void* dataset, const char* member_name, double* vector, int num_rows){
  ac_set_vector(dataset, member_name, vector, num_rows);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_matrix(void* dataset, const char* member_name, double* matrix, int num_rows, int num_cols){
  ac_set_matrix(dataset, member_name, matrix, num_rows, num_cols);
}
