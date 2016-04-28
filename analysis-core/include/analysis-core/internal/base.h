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
      virtual ~Base(){}
      
      template<class T> 
      boost::optional<typename std::enable_if<std::is_arithmetic<T>::value , T>::type> Get(const std::string& name){
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
      
      template<class T> 
      void Set(const std::string& name, typename std::enable_if<std::is_arithmetic<T>::value, T>::type value){
        members_[name] = std::make_shared<Member<T>>(value);
      }
      
      template<class T> 
      void Set(const std::string& name, typename std::enable_if<std::is_pointer<T>::value, T>::type value){
        members_[name] = std::make_shared<Member<T>>(value);
      }
      
      template<class T>
      void Set(const std::string& name, typename std::enable_if<mpl::has_key<Converters, T>::value, T>::type in){
        T m;
        auto member = std::make_shared<Member<T, typename mpl::at<Converters, T>::type>>(m);
        member->Set(in);
        members_[name] = member;
      }
      
      template<class T, class AT, class... Args>
      void Set(const std::string& name, typename std::enable_if<mpl::has_key<Converters, T>::value && std::is_pointer<AT>::value, AT>::type in, Args... args){
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

#endif //AC_BASE_H