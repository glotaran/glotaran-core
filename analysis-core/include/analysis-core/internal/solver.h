#ifndef SOLVER_H
#define SOLVER_H

#include "analysis-core/dataset.h"
#include "analysis-core/options.h"

#include "analysis-core/plugin/solverplugin.h"

namespace AnalysisCore
{
    class Solver {
      
    public:
      static bool Solve(const std::shared_ptr<SolverPlugin>& plugin, const std::vector<std::shared_ptr<Dataset>>& datasets, const std::shared_ptr<Options>& options);
    };
}

#endif //SOLVER_H