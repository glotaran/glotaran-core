#ifndef CORE_H
#define CORE_H

#include <memory>
#include <utility>
#include <vector>

#include "analysis-core_export.h"

#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

#include "analysis-core/internal/pluginmanager.h"

namespace AnalysisCore{

  class ANALYSIS_CORE_EXPORT Core{
    
  public:
    Core();
    ~Core();
    
    std::pair<std::shared_ptr<Dataset>, int> CreateDataset();
    void LinkDatasetParameter(const int from_id, const int to_id, const std::string& name);
    
    std::shared_ptr<Options> CreateOptions();
    
    bool SimulateUsingPlugin(const std::string& plugin_name, const std::shared_ptr<Dataset>& dataset, const std::shared_ptr<Options>& options);
    bool SimulateUsingPlugin(const std::string& plugin_name, const int dataset_id, const std::shared_ptr<Options>& options);
    
    bool SolveUsingPlugin(const std::string& plugin_name, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options);
    bool SolveUsingPlugin(const std::string& plugin_name, const std::vector<const int>& dataset_ids, const std::shared_ptr<Options>& options);
    
  private:
    int id;
    
    std::vector<std::shared_ptr<Dataset>> datasets_;
    
    PluginManager plugin_manager_;
    
  };

}

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef AnalysisCore::Core core_t;
  
  ANALYSIS_CORE_EXPORT void ac_init(core_t** core);
  ANALYSIS_CORE_EXPORT void ac_free(core_t* core);
  
  ANALYSIS_CORE_EXPORT void ac_create_dataset(core_t* core, void** dataset, int* id);
  ANALYSIS_CORE_EXPORT void ac_link_dataset_parameter(core_t* core, const int from_id, const int to_id, const char* member_name);
  
  ANALYSIS_CORE_EXPORT void ac_create_options(core_t* core, void** options);
  
  ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin(core_t* core, const char* plugin_name, void* dataset, void* options);
  ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin(core_t* core, const char* plugin_name, const int dataset_id, void* options);
  
  ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin(core_t* core, const char* plugin_name, void** datasets, const int number_of_datasets, void* options);
  ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin(core_t* core, const char* plugin_name, const int* dataset_ids, const int number_of_ids, void* options);
  
#ifdef __cplusplus
}
#endif

#endif // CORE_H
