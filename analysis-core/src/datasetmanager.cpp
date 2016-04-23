#include "analysis-core/datasetmanager.h"

using namespace AnalysisCore;

int DatasetManager::id = 0;

std::pair<std::shared_ptr<Dataset>, int> DatasetManager::CreateDataset(){
  auto d = std::make_shared<Dataset>(id);
  datasets_.push_back(d);
  auto p = std::make_pair(d, id);
  ++id;
  return p;
}

void DatasetManager::LinkDatasetParameter(const int from_id, const int to_id, const std::string& name){
  auto from = datasets_.at(from_id);
  auto to = datasets_.at(to_id);
  to->Set(name, from->Get(name));
}

ANALYSIS_CORE_EXPORT void ac_create_dataset(void** dataset, int* id){
  auto p = DatasetManager::CreateDataset();
  *dataset = static_cast<void*>(&p.first);
  *id = p.second;
}

ANALYSIS_CORE_EXPORT void ac_link_dataset_parameter(const int from_id, const int to_id, const char* member_name){
  DatasetManager::LinkDatasetParameter(from_id, to_id, std::string(member_name));
}