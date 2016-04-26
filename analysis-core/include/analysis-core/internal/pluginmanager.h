#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <memory>

#include <boost/filesystem/path.hpp>
#include <boost/dll.hpp>

#include "analysis-core/plugin/simulatorplugin.h"
#include "analysis-core/plugin/solverplugin.h"

namespace fs = boost::filesystem;

namespace AnalysisCore{

class PluginManager
{
  
public:
  PluginManager();
  ~PluginManager();
  
  void SetPluginPath(const std::string& path);
  void SetPluginPath(const fs::path& path);
  
  bool LoadPlugin(const std::string& name);
  bool LoadPlugin(const fs::path& name);
    
  bool LoadAllPlugins();
  
  std::shared_ptr<SimulatorPlugin> GetSimulatorPlugin(const std::string& name);
  std::shared_ptr<SolverPlugin> GetSolverPlugin(const std::string& name);
  
private:
  
  boost::filesystem::path plugin_path_;
  
  std::map<std::string, std::shared_ptr<SimulatorPlugin>> simulator_plugins_;
  std::map<std::string, std::shared_ptr<SolverPlugin>> solver_plugins_;
  
};

}

#endif // PLUGINMANAGER_H
