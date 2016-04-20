#include <limits>
#include <memory>

#include "analysis-core/internal/base.h"

static inline std::shared_ptr<AnalysisCore::internal::Base> get_base_from_void(void* base){
  return *static_cast<std::shared_ptr<AnalysisCore::internal::Base>*>(base);
}

bool ac_get_bool(void* base, const char* member_name){
  auto b = get_base_from_void(base);
  auto r = b->Get<bool>(std::string(member_name));
  return r.value_or(false);   
}

double ac_get_double(void* base, const char* member_name){
  auto b = get_base_from_void(base);
  auto r = b->Get<double>(std::string(member_name));
  return r.value_or(std::numeric_limits<double>::quiet_NaN());
}

double ac_get_int(void* base, const char* member_name){
  auto b = get_base_from_void(base);
  auto r = b->Get<int>(std::string(member_name));
  return r.value_or(std::numeric_limits<int>::min());
}

const char* ac_get_string(void* base, const char* member_name){
  auto b = get_base_from_void(base);
  return b->Get<const char*>(std::string(member_name));
}

double* ac_get_vector(void* base, const char* member_name, int* num_rows){
  auto b = get_base_from_void(base);
  return b->Get<vec, double*>(std::string(member_name), num_rows);
}

double* ac_get_matrix(void* base, const char* member_name, int* num_rows, int* num_cols){
  auto b = get_base_from_void(base);
  return b->Get<mat, double*>(std::string(member_name), num_rows, num_cols);
}

void ac_set_bool(void* base, const char* member_name, bool value){
  auto b = get_base_from_void(base);
  b->Set<bool>(std::string(member_name), value);
}

void ac_set_double(void* base, const char* member_name, double value){
  auto b = get_base_from_void(base);
  b->Set<double>(std::string(member_name), value);
}

void ac_set_int(void* base, const char* member_name, int value){
  auto b = get_base_from_void(base);
  b->Set<int>(std::string(member_name), value);
}

void ac_set_string(void* base, const char* member_name, const char* value){
  auto b = get_base_from_void(base);
  b->Set<const char*>(std::string(member_name), value);
}

void ac_set_vector(void* base, const char* member_name, double* vector, int num_rows){
  auto b = get_base_from_void(base);
  b->Set<vec, double*>(std::string(member_name), vector, num_rows);
}

void ac_get_matrix(void* base, const char* member_name, double* matrix, int num_rows, int num_cols){
  auto b = get_base_from_void(base);
  b->Set<mat, double*>(std::string(member_name), matrix, num_rows, num_cols);
}

