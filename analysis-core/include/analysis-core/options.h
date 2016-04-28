#ifndef OPTIONS_H
#define OPTIONS_H

#include <memory>

#include <ceres/solver.h>

#include "analysis-core/internal/member.h"
#include "analysis-core/internal/base.h"

using namespace AnaylsisCore::internal;

namespace AnalysisCore{
   
  class ANALYSIS_CORE_EXPORT Options : public internal::Base{
  
  public:
    virtual ~Options();
    
    ceres::Solver::Options& GetCeresOptions();
    void SetCeresOptions(ceres::Solver::Options& ceres_options);
    
  private:
    ANALYSIS_CORE_NO_EXPORT Options();
    ANALYSIS_CORE_NO_EXPORT static std::shared_ptr<Options> Create();
    
    ceres::Solver::Options ceres_options_;
    
    friend class Core;
    
#if defined(BOOST_GCC) || defined(BOOST_CLANG)
    friend void __gnu_cxx::new_allocator<Options>::construct<Options>(Options*);
#elif defined(BOOST_MSVC)
    friend class std::_Ref_count_obj;
#else
  #error Unsupported compiler
#endif
  };
  
}

#endif // OPTIONS_H