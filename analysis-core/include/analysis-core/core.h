#ifndef CORE_H
#define CORE_H

#include <memory>
#include <utility>
#include <vector>

#include "analysis-core/dataset.h"

#include "analysis-core_export.h"

namespace ANALYSIS_CORE_EXPORT AnalysisCore{

  class Core
  {
    
  public:
    Core();
    ~Core();
    
    std::pair<std::shared_ptr<Dataset>, int> CreateDataset();
    void LinkDatasetParameter(const int from_id, const int to_id, const std::string& name);
    
  private:
    int id;
    std::vector<std::shared_ptr<Dataset>> datasets_;
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

    
#ifdef __cplusplus
}
#endif

#endif // CORE_H
