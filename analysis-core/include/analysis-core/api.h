#ifndef API_H
#define API_H

#include <stdbool.h>

#include "analysis-core_export.h"

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct core_s core_t;
  
  ANALYSIS_CORE_EXPORT core_t* ac_init();
  ANALYSIS_CORE_EXPORT void ac_free(core_t* core);
  
  ANALYSIS_CORE_EXPORT void ac_create_dataset(core_t* core, void** dataset, int* id);
  ANALYSIS_CORE_EXPORT void ac_link_dataset_parameter(core_t* core, const int from_id, const int to_id, const char* member_name);
  
  ANALYSIS_CORE_EXPORT void ac_create_options(core_t* core, void** options);
  
  ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin_with_dataset(core_t* core, const char* plugin_name, void* dataset, void* options);
  ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin_with_id(core_t* core, const char* plugin_name, const int dataset_id, void* options);
  
  ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin_with_datasets(core_t* core, const char* plugin_name, void** datasets, const int number_of_datasets, void* options);
  ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin_with_ids(core_t* core, const char* plugin_name, int* dataset_ids, const int number_of_ids, void* options);
  
  ANALYSIS_CORE_EXPORT bool ac_dataset_get_bool(void* dataset, const char* member_name);
  ANALYSIS_CORE_EXPORT double ac_dataset_get_double(void* dataset, const char* member_name);
  ANALYSIS_CORE_EXPORT int ac_dataset_get_int(void* dataset, const char* member_name);
  ANALYSIS_CORE_EXPORT const char* ac_dataset_get_string(void* dataset, const char* member_name);
  ANALYSIS_CORE_EXPORT void* ac_dataset_get_arbitrary(void* dataset, const char* member_name);
  ANALYSIS_CORE_EXPORT double* ac_dataset_get_vector(void* dataset, const char* member_name, int* num_rows);
  ANALYSIS_CORE_EXPORT double* ac_dataset_get_matrix(void* dataset, const char* member_name, int* num_rows, int* num_cols);
  
  ANALYSIS_CORE_EXPORT void ac_dataset_set_bool(void* dataset, const char* member_name, bool value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_double(void* dataset, const char* member_name, double value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_int(void* dataset, const char* member_name, int value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_string(void* dataset, const char* member_name, const char* value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_arbitrary(void* dataset, const char* member_name, void* value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_vector(void* dataset, const char* member_name, double* vector, int num_rows);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_matrix(void* dataset, const char* member_name, double* matrix, int num_rows, int num_cols);
  
  
  ANALYSIS_CORE_EXPORT bool ac_options_get_bool(void* options, const char* member_name);
  ANALYSIS_CORE_EXPORT double ac_options_get_double(void* options, const char* member_name);
  ANALYSIS_CORE_EXPORT int ac_options_get_int(void* options, const char* member_name);
  ANALYSIS_CORE_EXPORT const char* ac_options_get_string(void* options, const char* member_name);
  ANALYSIS_CORE_EXPORT void* ac_options_get_arbitrary(void* options, const char* member_name);
  ANALYSIS_CORE_EXPORT double* ac_options_get_vector(void* options, const char* member_name, int* num_rows);
  ANALYSIS_CORE_EXPORT double* ac_options_get_matrix(void* options, const char* member_name, int* num_rows, int* num_cols);
  
  ANALYSIS_CORE_EXPORT void ac_options_set_bool(void* options, const char* member_name, bool value);
  ANALYSIS_CORE_EXPORT void ac_options_set_double(void* options, const char* member_name, double value);
  ANALYSIS_CORE_EXPORT void ac_options_set_int(void* options, const char* member_name, int value);
  ANALYSIS_CORE_EXPORT void ac_options_set_string(void* options, const char* member_name, const char* value);
  ANALYSIS_CORE_EXPORT void ac_options_set_arbitrary(void* options, const char* member_name, void* value);
  ANALYSIS_CORE_EXPORT void ac_options_set_vector(void* options, const char* member_name, double* vector, int num_rows);
  ANALYSIS_CORE_EXPORT void ac_options_set_matrix(void* options, const char* member_name, double* matrix, int num_rows, int num_cols);
  
#ifdef __cplusplus
}
#endif

#endif //API_H