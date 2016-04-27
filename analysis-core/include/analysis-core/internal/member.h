#ifndef MEMBER_H
#define MEMBER_H

#include <type_traits>

#include <armadillo>

using namespace arma;

namespace AnaylsisCore{
  namespace internal{
    class MemberBase{
    public:
      MemberBase(){}
      virtual ~MemberBase(){}
    };
    
    template<class...> class Member;
    
    template<class T>
    class Member<T> : public MemberBase{

    public:
      typedef T type;
      
      Member(T& m) : m_(m){}
      
      virtual ~Member<T>(){}
      
      T Get(){
        return m_;
      }
      
      void Set(T& m){
        m_ = m;
      }
      
    protected:
      T m_;
    };

    template<class T>
    class Member<T*> : public MemberBase{

    public:
      typedef T* type;
      
      Member(T* m) : m_(m){}
      
      virtual ~Member<T*>(){}
      
      T* Get(){
        return m_;
      }
      
      void Set(T* m){
        m_ = m;
      }
      
    protected:
      T* m_;
    };
    
    template<class T, class Converter>
    class Member<T, Converter> : public Member<T>{
    
    static_assert(std::is_same<T, typename Converter::type>::value, "Wrong Converter type");
        
    public:
      Member(T& m) : Member<T>(m){}
      
      virtual ~Member<T, Converter>(){}
       
      T Get(){
        return Member<T>::Get();
      }
      
      void Set(T m){
        return Member<T>::Set(m);
      }
       
      template<class AT, class... Args> AT Get(Args... args){
        Converter c;
        return c.Get(this->m_, args...);
      }
      
      template<class AT, class... Args> void Set(AT arg, Args... args){
        Converter c;
        c.Set(this->m_, arg, args...);
      }
      
    };
    
  }
}

#endif // MEMBER_H