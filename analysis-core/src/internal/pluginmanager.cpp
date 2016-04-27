#include "analysis-core/internal/pluginmanager.h"

using namespace AnalysisCore;

namespace dll = boost::dll;
namespace fs = boost::filesystem;

PluginManager::PluginManager(){
  plugin_path_ = dll::program_location().parent_path() / fs::path("../plugins");
}

PluginManager::~PluginManager(){

}

void PluginManager::SetPluginPath(const std::string& path){
  SetPluginPath(fs::path(path));
}

void PluginManager::SetPluginPath(const fs::path& path){
  plugin_path_ = path;
}

bool PluginManager::LoadPlugin(const std::string& name){
  return LoadPlugin(fs::path(name));
}

bool PluginManager::LoadPlugin(const boost::filesystem::path& name){
  if(!fs::exists(name) || !fs::is_regular_file(name))
    return false;
  
  if(name.has_stem() && name.stem().generic_string().find("_sim") != std::string::npos){
    auto simulator = dll::import<SimulatorPlugin>(name, "simulator");
    simulator_plugins_[simulator->Name()] = std::shared_ptr<SimulatorPlugin>(simulator.get(), [simulator](SimulatorPlugin*) mutable {simulator.reset();});
    return true;
  }
  else if(name.has_stem() && name.stem().generic_string().rfind("_sol") != std::string::npos){
    auto solver = dll::import<SolverPlugin>(name, "solver");
    solver_plugins_[solver->Name()] = std::shared_ptr<SolverPlugin>(solver.get(), [solver](SolverPlugin*) mutable {solver.reset();});
    return true;
  }
  else
    return false;
  
  return false;
}

void PluginManager::LoadAllPlugins(){
  if(!fs::is_directory(plugin_path_))
    return;
  
  for(auto&& name : fs::directory_iterator(plugin_path_)){
    if(!fs::is_regular_file(name))
      continue;
    LoadPlugin(name.path());
  }
}

std::shared_ptr<SimulatorPlugin> PluginManager::GetSimulatorPlugin(const std::string& name){
  return simulator_plugins_[name];
}

std::shared_ptr<SolverPlugin> PluginManager::GetSolverPlugin(const std::string& name){
  return solver_plugins_[name];
}

