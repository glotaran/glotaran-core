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
    //ANALYSIS_CORE_NO_EXPORT static Dataset* Create(int& id);
    
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

#endif // DATASET_H
