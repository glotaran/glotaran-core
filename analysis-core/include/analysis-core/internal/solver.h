#ifndef SOLVER_H
#define SOLVER_H

#include <armadillo>

#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

#include "analysis-core/plugin/solverplugin.h"

using namespace arma;

namespace AnalysisCore
{
    class Solver {
      
    public:
      static bool Solve(const std::shared_ptr<SolverPlugin>& plugin, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options);
      
    private:
      static std::map<std::string, mat> parameters_;
    };
}

#endif //SOLVER_H