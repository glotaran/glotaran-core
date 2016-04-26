#include "analysis-core/internal/pluginmanager.h"

using namespace AnalysisCore;

namespace dll = boost::dll;
namespace fs = boost::filesystem;

PluginManager::PluginManager(){
  plugin_path_ = fs::path("../plugins");
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
  
  boost::system::error_code error;
  
  dll::shared_library plugin(name, error);
  
  if(error)
    return false;
  
  if(name.has_stem() && name.stem().generic_string().find("sim") != std::string::npos){
    auto simulator = dll::import<SimulatorPlugin>(name, "simulator");
    simulator_plugins_[simulator->Name()] = std::shared_ptr<SimulatorPlugin>(simulator.get(), [simulator](SimulatorPlugin*) mutable {simulator.reset();});
    return true;
  }
  else if(name.has_stem() && name.stem().generic_string().rfind("sol") != std::string::npos){
    auto solver = dll::import<SolverPlugin>(name, "solver");
    solver_plugins_[solver->Name()] = std::shared_ptr<SolverPlugin>(solver.get(), [solver](SolverPlugin*) mutable {solver.reset();});
    return true;
  }
  else
    return false;
  
  return false;
}

bool PluginManager::LoadAllPlugins(){
  if(!fs::is_directory(plugin_path_))
    return false;
  
  bool success = true;
  
  for(auto&& name : fs::recursive_directory_iterator(plugin_path_)){
    if(!fs::is_regular_file(name))
      continue;
    if(name.path().has_stem()
      && (name.path().stem().generic_string().rfind("_simulator") == std::string::npos
      || name.path().stem().generic_string().rfind("_solver") == std::string::npos))
        continue;
    success &= LoadPlugin(name.path());
  }
  
  return success;
      
}
