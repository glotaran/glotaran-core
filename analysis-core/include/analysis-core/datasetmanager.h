#ifndef DATASETMANAGER_H
#define DATASETMANAGER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "dataset.h"

namespace AnalysisCore{

  class DatasetManager
  {
  public:
    static std::pair<std::shared_ptr<Dataset>, int> CreateDataset();
    static void LinkDatasetParameter(const int from_id, const int to_id, const std::string& name);
  
  private:
    static int id;
    
    static std::vector<std::shared_ptr<Dataset>> datasets_;
  };

}

#ifdef __cplusplus
extern "C" {
#endif
  
  ANALYSIS_CORE_EXPORT void ac_create_dataset(void** dataset, int* id);
  ANALYSIS_CORE_EXPORT void ac_link_dataset_parameter(const int from_id, const int to_id, const char* member_name);

    
#ifdef __cplusplus
}
#endif

#endif // DATASETMANAGER_H
