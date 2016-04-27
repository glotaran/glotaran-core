#ifndef DATASET_H
#define DATASET_H

#include <memory>

#include <boost/config.hpp>

#include "analysis-core/internal/member.h"
#include "analysis-core/internal/base.h"

using namespace AnaylsisCore::internal;

namespace AnalysisCore{
   
  class ANALYSIS_CORE_EXPORT Dataset : public internal::Base{
  
  public:
    virtual ~Dataset();
    
    int GetId();
    
    std::shared_ptr<MemberBase> GetMember(const std::string& name);
    void SetMember(const std::string& name, std::shared_ptr<MemberBase> member);

  private:
    ANALYSIS_CORE_NO_EXPORT Dataset(int& id);
    
    ANALYSIS_CORE_NO_EXPORT static std::shared_ptr<Dataset> Create(int& id);
    
    int id_;
    
    friend class Core;
    
#if defined(BOOST_GCC) || defined(BOOST_CLANG)
    friend void __gnu_cxx::new_allocator<Dataset>::construct<Dataset, int&>(Dataset*, int&);
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
  
  static inline std::shared_ptr<AnalysisCore::Dataset> get_dataset_from_void(void* dataset){
    return *static_cast<std::shared_ptr<AnalysisCore::Dataset>*>(dataset);
  }

  ANALYSIS_CORE_EXPORT bool ac_dataset_get_bool(void* dataset, char* member_name);
  ANALYSIS_CORE_EXPORT double ac_dataset_get_double(void* dataset, char* member_name);
  ANALYSIS_CORE_EXPORT int ac_dataset_get_int(void* dataset, char* member_name);
  ANALYSIS_CORE_EXPORT const char* ac_dataset_get_string(void* dataset, char* member_name);
  ANALYSIS_CORE_EXPORT void* ac_dataset_get_arbitrary(void* dataset, char* member_name);
  ANALYSIS_CORE_EXPORT double* ac_dataset_get_vector(void* dataset, char* member_name, int* num_rows);
  ANALYSIS_CORE_EXPORT double* ac_dataset_get_matrix(void* dataset, char* member_name, int* num_rows, int* num_cols);
  
  ANALYSIS_CORE_EXPORT void ac_dataset_set_bool(void* dataset, char* member_name, bool value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_double(void* dataset, char* member_name, double value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_int(void* dataset, char* member_name, int value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_string(void* dataset, char* member_name, const char* value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_arbitrary(void* dataset, char* member_name, void* value);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_vector(void* dataset, char* member_name, double* vector, int num_rows);
  ANALYSIS_CORE_EXPORT void ac_dataset_set_matrix(void* dataset, char* member_name, double* matrix, int num_rows, int num_cols);

    
#ifdef __cplusplus
}
#endif

#endif // DATASET_H
