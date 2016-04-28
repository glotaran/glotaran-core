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
    bool SolveUsingPlugin(const std::string& plugin_name, const std::vector<int>& dataset_ids, const std::shared_ptr<Options>& options);
    
    std::shared_ptr<Dataset> FindDataset(const Dataset* dataset);
    std::shared_ptr<Options> FindOptions(const Options* options);
    
  private:
    int id;
    
    std::vector<std::shared_ptr<Dataset>> datasets_;
    std::vector<std::shared_ptr<Options>> options_;
    
    PluginManager plugin_manager_;
    
  };
  
}

#endif // CORE_H
