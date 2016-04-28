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
  auto o = Options::Create();
  options_.push_back(o);
  return o;
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

std::shared_ptr<Dataset> Core::FindDataset(const Dataset* dataset){
  for(auto&& d : datasets_){
    if(d.get() == dataset)
      return d;
  }
}

std::shared_ptr<Options> Core::FindOptions(const Options* options){
  for(auto&& o : options_){
    if(o.get() == options)
      return o;
  }
}
