#ifndef AC_BASE_H
#define AC_BASE_H

#include <map>
#include <memory>
#include <string>
#include <type_traits>

#include <boost/optional.hpp>

#include <boost/polymorphic_pointer_cast.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/map.hpp>

#include <armadillo>

#include "analysis-core_export.h"

#include "analysis-core/internal/member.h"
#include "analysis-core/internal/converter.h"

using namespace arma;

namespace mpl = boost::mpl;

using namespace AnaylsisCore::internal;

namespace AnalysisCore{
  namespace internal{
    class Base{
      
    public:
      virtual ~Base();
      
      template<class T> 
      boost::optional<typename std::enable_if<std::is_arithmetic<T>::value, T>::type> Get(const std::string& name){
        auto m = members_[name];
        if(!m)
          return boost::none;
        auto member = boost::polymorphic_pointer_downcast<Member<T>>(m);
        return member->Get();
      }
      
      template<class T>
      boost::optional<typename std::enable_if<mpl::has_key<Converters, T>::value, T>::type> Get(const std::string& name){
        auto m = members_[name];
        if(!m)
          return boost::none;
        auto member = boost::polymorphic_pointer_downcast<Member<T>>(m);
        return member->Get();
      }
      
      template<class T>
      typename std::enable_if<std::is_pointer<T>::value, T>::type Get(const std::string& name){
        auto m = members_[name];
        if(!m)
          return nullptr;
        auto member = boost::polymorphic_pointer_downcast<Member<T>>(m);
        return member->Get();
      }
      
      template<class T, class AT, class... Args> AT Get(const std::string& name, Args... args){
        auto m = members_[name];
        if(!m && std::is_pointer<AT>::value)
          return nullptr;
        auto member = boost::polymorphic_pointer_downcast<Member<T, typename mpl::at<Converters, T>::type>>(m);
        return member->Get<AT>(args...);
      }
      
      template<class T> void Set(const std::string& name, T& value){
        members_[name] = std::make_shared<Member<T>>(value);
      }
      
      template<class T>
      void Set(const std::string& name, typename std::enable_if<mpl::has_key<Converters, T>::value, T>::type in){
        T m;
        auto member = std::make_shared<Member<T, typename mpl::at<Converters, T>::type>>(m);
        member->Set(in);
        members_[name] = member;
      }
      
      template<class T, class AT, class... Args> void Set(const std::string& name, AT in, Args... args){
        T m;
        auto member = std::make_shared<Member<T, typename mpl::at<Converters, T>::type>>(m);
        member->Set<AT>(in, args...);
        members_[name] = member;
      }

    protected:
      std::map<std::string, std::shared_ptr<MemberBase>> members_;
      
    };
    
  }
}

#ifdef __cplusplus
extern "C" {
#endif
  
  bool ac_get_bool(void* base, const char* member_name);
  double ac_get_double(void* base, const char* member_name);
  double ac_get_int(void* base, const char* member_name);
  const char* ac_get_string(void* base, const char* member_name);
  void* ac_get_arbitrary(void* base, const char* member_name);
  double* ac_get_vector(void* base, const char* member_name, int* num_rows);
  double* ac_get_matrix(void* base, const char* member_name, int* num_rows, int* num_cols);
  
  void ac_set_bool(void* base, const char* member_name, bool value);
  void ac_set_double(void* base, const char* member_name, double value);
  void ac_set_int(void* base, const char* member_name, int value);
  void ac_set_string(void* base, const char* member_name, const char* value);
  void ac_set_arbitrary(void* base, const char* member_name, void* value);
  void ac_set_vector(void* base, const char* member_name, double* vector, int num_rows);
  void ac_set_matrix(void* base, const char* member_name, double* matrix, int num_rows, int num_cols);

    
#ifdef __cplusplus
}
#endif

#endif //AC_BASE_H