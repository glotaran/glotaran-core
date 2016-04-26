#include <memory>

#include "analysis-core/internal/base.h"
#include "analysis-core/dataset.h"

using namespace AnalysisCore;

Dataset::Dataset(int& id) : id_(id){

}

std::shared_ptr<Dataset>&& Dataset::Create(int& id){
  return std::move(std::make_shared<Dataset>(id));
}

Dataset::~Dataset(){

}

int Dataset::GetId(){
  return id_;
}

std::shared_ptr<MemberBase> Dataset::GetMember(const std::string& name){
  return members_[name];
}

void Dataset::SetMember(const std::string& name, std::shared_ptr<MemberBase> member){
  members_[name] = member;
}

ANALYSIS_CORE_EXPORT bool ac_dataset_get_bool(void* dataset, const char* member_name){
  return ac_get_bool(dataset, member_name);
}

ANALYSIS_CORE_EXPORT double ac_dataset_get_double(void* dataset, const char* member_name){
  return ac_get_double(dataset, member_name);
}

ANALYSIS_CORE_EXPORT int ac_dataset_get_int(void* dataset, const char* member_name){
  return ac_get_int(dataset, member_name);
}

ANALYSIS_CORE_EXPORT const char* ac_dataset_get_string(void* dataset, const char* member_name){
  return ac_get_string(dataset, member_name);
}

ANALYSIS_CORE_EXPORT void* ac_dataset_get_arbitrary(void* dataset, const char* member_name){
  return ac_get_arbitrary(dataset, member_name);
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

ANALYSIS_CORE_EXPORT void ac_dataset_set_int(void* dataset, const char* member_name, int value){
  ac_set_int(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_string(void* dataset, const char* member_name, const char* value){
  ac_set_string(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_arbitrary(void* dataset, const char* member_name, void* value){
  ac_set_arbitrary(dataset, member_name, value);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_vector(void* dataset, const char* member_name, double* vector, int num_rows){
  ac_set_vector(dataset, member_name, vector, num_rows);
}

ANALYSIS_CORE_EXPORT void ac_dataset_set_matrix(void* dataset, const char* member_name, double* matrix, int num_rows, int num_cols){
  ac_set_matrix(dataset, member_name, matrix, num_rows, num_cols);
}
