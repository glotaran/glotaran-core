#include <memory>

#include "analysis-core/api.h"

#include "analysis-core/internal/base.h"

#include "analysis-core/core.h"
#include "analysis-core/dataset.h"

using AnalysisCore::Core;
using AnalysisCore::Dataset;
using AnalysisCore::Options;

inline Dataset* get_dataset_from_void(void* dataset){
  return static_cast<Dataset*>(dataset);
}

inline Options* get_options_from_void(void* options){
  return static_cast<Options*>(options);
}

core_t* ac_init(){
  return reinterpret_cast<core_t*>(new Core);
}

void ac_free(core_t* core){
  delete reinterpret_cast<Core*>(core);
}

void ac_create_dataset(core_t* core, void** dataset, int* id){
  auto p = (reinterpret_cast<Core*>(core))->CreateDataset();
  auto d = p.first;
  *dataset = reinterpret_cast<void*>(d.get());
  *id = p.second;
}

void ac_link_dataset_parameter(core_t* core, const int from_id, const int to_id, const char* member_name){
  (reinterpret_cast<Core*>(core))->LinkDatasetParameter(from_id, to_id, std::string(member_name));
}

void ac_create_options(core_t* core, void** options){
  auto o = (reinterpret_cast<Core*>(core))->CreateOptions();
  *options = reinterpret_cast<void*>(o.get());
}

bool ac_simulate_using_plugin_with_dataset(core_t* core, const char* plugin_name, void* dataset, void* options){
  auto d = get_dataset_from_void(dataset);
  auto ds = (reinterpret_cast<Core*>(core))->FindDataset(d);
  
  auto o = get_options_from_void(options);
  auto op = (reinterpret_cast<Core*>(core))->FindOptions(o);
  
  return (reinterpret_cast<Core*>(core))->SimulateUsingPlugin(std::string(plugin_name), ds, op);
}

bool ac_simulate_using_plugin_with_id(core_t* core, const char* plugin_name, const int dataset_id, void* options){
  auto o = get_options_from_void(options);
  auto op = (reinterpret_cast<Core*>(core))->FindOptions(o)
  ;
  return (reinterpret_cast<Core*>(core))->SimulateUsingPlugin(std::string(plugin_name), dataset_id, op);
}
  
bool ac_solve_using_plugin_with_datasets(core_t* core, const char* plugin_name, void** datasets, const int number_of_datasets, void* options){
  std::vector<std::shared_ptr<Dataset>> data;
  
  auto o = get_options_from_void(options);
  auto op = (reinterpret_cast<Core*>(core))->FindOptions(o);
  
  for(int i = 0; i < number_of_datasets; ++i){
    auto d = get_dataset_from_void(datasets[i]);
    auto ds = (reinterpret_cast<Core*>(core))->FindDataset(d);
    data.push_back(ds);
  }
  
  return (reinterpret_cast<Core*>(core))->SolveUsingPlugin(std::string(plugin_name), data, op);
}

bool ac_solve_using_plugin_with_ids(core_t* core, const char* plugin_name, const int* dataset_ids, const int number_of_ids, void* options){
  std::vector<int> datasets;
  
  auto o = get_options_from_void(options);
  auto op = (reinterpret_cast<Core*>(core))->FindOptions(o);
  
  for(int i = 0; i < number_of_ids; ++i){
    datasets.push_back(dataset_ids[i]);
  }
  
  return (reinterpret_cast<Core*>(core))->SolveUsingPlugin(std::string(plugin_name), datasets, op);
}

bool ac_dataset_get_bool(void* dataset, const char* member_name){
  auto d = get_dataset_from_void(dataset);
  auto r = d->Get<bool>(std::string(member_name));
  return r.value_or(false);   
}

double ac_dataset_get_double(void* dataset, const char* member_name){
  auto d = get_dataset_from_void(dataset);
  auto r = d->Get<double>(std::string(member_name));
  return r.value_or(std::numeric_limits<double>::quiet_NaN());
}

int ac_dataset_get_int(void* dataset, const char* member_name){
  auto d = get_dataset_from_void(dataset);
  auto r = d->Get<int>(std::string(member_name));
  return r.value_or(std::numeric_limits<int>::min());
}

const char* ac_dataset_get_string(void* dataset, const char* member_name){
  auto d = get_dataset_from_void(dataset);
  return d->Get<const char*>(std::string(member_name));
}

void* ac_dataset_get_arbitrary(void* dataset, const char* member_name){
  auto d = get_dataset_from_void(dataset);
  return d->Get<void*>(std::string(member_name));
}

double* ac_dataset_get_vector(void* dataset, const char* member_name, int* num_rows){
  auto d = get_dataset_from_void(dataset);
  return d->Get<vec, double*>(std::string(member_name), num_rows);
}

double* ac_dataset_get_matrix(void* dataset, const char* member_name, int* num_rows, int* num_cols){
  auto d = get_dataset_from_void(dataset);
  return d->Get<mat, double*>(std::string(member_name), num_rows, num_cols);
}

void ac_dataset_set_bool(void* dataset, const char* member_name, bool value){
  auto d = get_dataset_from_void(dataset);
  d->Set<bool>(std::string(member_name), value);
}

void ac_dataset_set_double(void* dataset, const char* member_name, double value){
  auto d = get_dataset_from_void(dataset);
  d->Set<double>(std::string(member_name), value);
}

void ac_dataset_set_int(void* dataset, const char* member_name, int value){
  auto d = get_dataset_from_void(dataset);
  d->Set<int>(std::string(member_name), value);
}

void ac_dataset_set_string(void* dataset, const char* member_name, const char* value){
  auto d = get_dataset_from_void(dataset);
  d->Set<const char*>(std::string(member_name), value);
}

void ac_dataset_set_arbitrary(void* dataset, const char* member_name, void* value){
  auto d = get_dataset_from_void(dataset);
  d->Set<void*>(std::string(member_name), value);
}

void ac_dataset_set_vector(void* dataset, const char* member_name, double* vector, int num_rows){
  auto d = get_dataset_from_void(dataset);
  d->Set<vec, double*>(std::string(member_name), vector, num_rows);
}

void ac_dataset_set_matrix(void* dataset, const char* member_name, double* matrix, int num_rows, int num_cols){
  auto d = get_dataset_from_void(dataset);
  d->Set<mat, double*>(std::string(member_name), matrix, num_rows, num_cols);
}

bool ac_options_get_bool(void* options, const char* member_name){
  auto o = get_options_from_void(options);
  auto r = o->Get<bool>(std::string(member_name));
  return r.value_or(false);   
}

double ac_options_get_double(void* options, const char* member_name){
  auto o = get_options_from_void(options);
  auto r = o->Get<double>(std::string(member_name));
  return r.value_or(std::numeric_limits<double>::quiet_NaN());
}

int ac_options_get_int(void* options, const char* member_name){
  auto o = get_options_from_void(options);
  auto r = o->Get<int>(std::string(member_name));
  return r.value_or(std::numeric_limits<int>::min());
}

const char* ac_options_get_string(void* options, const char* member_name){
  auto o = get_options_from_void(options);
  return o->Get<const char*>(std::string(member_name));
}

void* ac_options_get_arbitrary(void* options, const char* member_name){
  auto o = get_options_from_void(options);
  return o->Get<void*>(std::string(member_name));
}

double* ac_options_get_vector(void* options, const char* member_name, int* num_rows){
  auto o = get_options_from_void(options);
  return o->Get<vec, double*>(std::string(member_name), num_rows);
}

double* ac_options_get_matrix(void* options, const char* member_name, int* num_rows, int* num_cols){
  auto o = get_options_from_void(options);
  return o->Get<mat, double*>(std::string(member_name), num_rows, num_cols);
}

void ac_options_set_bool(void* options, const char* member_name, bool value){
  auto o = get_options_from_void(options);
  o->Set<bool>(std::string(member_name), value);
}

void ac_options_set_double(void* options, const char* member_name, double value){
  auto o = get_options_from_void(options);
  o->Set<double>(std::string(member_name), value);
}

void ac_options_set_int(void* options, const char* member_name, int value){
  auto o = get_options_from_void(options);
  o->Set<int>(std::string(member_name), value);
}

void ac_options_set_string(void* options, const char* member_name, const char* value){
  auto o = get_options_from_void(options);
  o->Set<const char*>(std::string(member_name), value);
}

void ac_options_set_arbitrary(void* options, const char* member_name, void* value){
  auto o = get_options_from_void(options);
  o->Set<void*>(std::string(member_name), value);
}

void ac_options_set_vector(void* options, const char* member_name, double* vector, int num_rows){
  auto o = get_options_from_void(options);
  o->Set<vec, double*>(std::string(member_name), vector, num_rows);
}

void ac_options_set_matrix(void* options, const char* member_name, double* matrix, int num_rows, int num_cols){
  auto o = get_options_from_void(options);
  o->Set<mat, double*>(std::string(member_name), matrix, num_rows, num_cols);
}