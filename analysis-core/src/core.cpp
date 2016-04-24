#include "analysis-core/core.h"

using namespace AnalysisCore;

Core::Core(){
  id = 0;
}

Core::~Core(){

}

std::pair<std::shared_ptr<Dataset>, int> Core::CreateDataset(){
  auto d = std::make_shared<Dataset>(id);
  datasets_.push_back(d);
  auto p = std::make_pair(d, id);
  ++id;
  return p;
}

void Core::LinkDatasetParameter(const int from_id, const int to_id, const std::string& name){
  auto from = datasets_.at(from_id);
  auto to = datasets_.at(to_id);
  to->Set(name, from->Get(name));
}

ANALYSIS_CORE_EXPORT void ac_init(core_t** core){
  *core = new AnalysisCore::Core();
}

ANALYSIS_CORE_EXPORT void ac_free(core_t* core){
  delete core;
}

ANALYSIS_CORE_EXPORT void ac_create_dataset(core_t* core, void** dataset, int* id){
  auto p = core->CreateDataset();
  *dataset = static_cast<void*>(&p.first);
  *id = p.second;
}

ANALYSIS_CORE_EXPORT void ac_link_dataset_parameter(core_t* core, const int from_id, const int to_id, const char* member_name){
  core->LinkDatasetParameter(from_id, to_id, std::string(member_name));
}