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

#ifdef __cplusplus
extern "C" {
#endif
  
  static inline std::shared_ptr<AnalysisCore::Options> get_options_from_void(void* options){
    return *static_cast<std::shared_ptr<AnalysisCore::Options>*>(options);
  }

  ANALYSIS_CORE_EXPORT bool ac_options_get_bool(void* options, char* member_name);
  ANALYSIS_CORE_EXPORT double ac_options_get_double(void* options, char* member_name);
  ANALYSIS_CORE_EXPORT int ac_options_get_int(void* options, char* member_name);
  ANALYSIS_CORE_EXPORT char* ac_options_get_string(void* options, char* member_name);
  ANALYSIS_CORE_EXPORT void* ac_options_get_arbitrary(void* options, char* member_name);
  ANALYSIS_CORE_EXPORT double* ac_options_get_vector(void* options, char* member_name, int* num_rows);
  ANALYSIS_CORE_EXPORT double* ac_options_get_matrix(void* options, char* member_name, int* num_rows, int* num_cols);
  
  ANALYSIS_CORE_EXPORT void ac_options_set_bool(void* options, char* member_name, bool value);
  ANALYSIS_CORE_EXPORT void ac_options_set_double(void* options, char* member_name, double value);
  ANALYSIS_CORE_EXPORT void ac_options_set_int(void* options, char* member_name, int value);
  ANALYSIS_CORE_EXPORT void ac_options_set_string(void* options, char* member_name, const char* value);
  ANALYSIS_CORE_EXPORT void ac_options_set_arbitrary(void* options, char* member_name, void* value);
  ANALYSIS_CORE_EXPORT void ac_options_set_vector(void* options, char* member_name, double* vector, int num_rows);
  ANALYSIS_CORE_EXPORT void ac_options_set_matrix(void* options, char* member_name, double* matrix, int num_rows, int num_cols);

    
#ifdef __cplusplus
}
#endif

#endif // OPTIONS_H