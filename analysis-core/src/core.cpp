#include "analysis-core/core.h"

#include "analysis-core/dataset.h"

#include "analysis-core/internal/solver.h"
#include "analysis-core/internal/simulator.h"

using namespace AnalysisCore;

Core::Core(){
  id = 0;
  plugin_manager_.LoadAllPlugins();
}

Core::~Core(){

}

std::pair<std::shared_ptr<Dataset>, int> Core::CreateDataset(){
  auto d = Dataset::Create(id);
  datasets_.push_back(d);
  auto p = std::make_pair(d, id);
  ++id;
  return p;
}

void Core::LinkDatasetParameter(const int from_id, const int to_id, const std::string& name){
  auto from = datasets_.at(from_id);
  auto to = datasets_.at(to_id);
  to->SetMember(name, from->GetMember(name));
}

std::shared_ptr<Options> Core::CreateOptions(){
  return Options::Create();
}

bool Core::SimulateUsingPlugin(const std::string& plugin_name, const std::shared_ptr<Dataset>& dataset, const std::shared_ptr<Options>& options){
  auto plugin = plugin_manager_.GetSimulatorPlugin(plugin_name);
  return Simulator::Simulate(plugin, dataset, options);
}

bool Core::SimulateUsingPlugin(const std::string& plugin_name, const int dataset_id, const std::shared_ptr<Options>& options){
  auto dataset = datasets_.at(dataset_id);
  return SimulateUsingPlugin(plugin_name, dataset, options);
}

bool Core::SolveUsingPlugin(const std::string& plugin_name, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options){
  auto plugin = plugin_manager_.GetSolverPlugin(plugin_name);
  return Solver::Solve(plugin, datasets, options);
}

bool Core::SolveUsingPlugin(const std::string& plugin_name, const std::vector<int>& dataset_ids, const std::shared_ptr<Options>& options){
  std::vector<std::shared_ptr<Dataset>> datasets;
  
  for(auto& id : dataset_ids)
    datasets.push_back(datasets_.at(id));
  
  return SolveUsingPlugin(plugin_name, datasets, options);
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

ANALYSIS_CORE_EXPORT void ac_create_options(core_t* core, void** options){
  auto o = core->CreateOptions();
  *options = static_cast<void*>(&o);
}

ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin_with_dataset(core_t* core, const char* plugin_name, void* dataset, void* options){
  auto d = get_dataset_from_void(dataset);
  auto o = get_options_from_void(options);
  return core->SimulateUsingPlugin(std::string(plugin_name), d, o);
}

ANALYSIS_CORE_EXPORT bool ac_simulate_using_plugin_with_id(core_t* core, const char* plugin_name, const int dataset_id, void* options){
  auto o = get_options_from_void(options);
  return core->SimulateUsingPlugin(std::string(plugin_name), dataset_id, o);
}
  
ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin_with_datasets(core_t* core, const char* plugin_name, void** datasets, const int number_of_datasets, void* options){
  std::vector<std::shared_ptr<Dataset>> ds;
  auto o = get_options_from_void(options);
  
  for(int i = 0; i < number_of_datasets; ++i){
    auto d = get_dataset_from_void(datasets[i]);
    ds.push_back(d);
  }
  
  return core->SolveUsingPlugin(std::string(plugin_name), ds, o);
}

ANALYSIS_CORE_EXPORT bool ac_solve_using_plugin_with_ids(core_t* core, const char* plugin_name, const int* dataset_ids, const int number_of_ids, void* options){
  std::vector<int> ds;
  auto o = get_options_from_void(options);
  
  for(int i = 0; i < number_of_ids; ++i){
    ds.push_back(dataset_ids[i]);
  }
  
  return core->SolveUsingPlugin(std::string(plugin_name), ds, o);
}