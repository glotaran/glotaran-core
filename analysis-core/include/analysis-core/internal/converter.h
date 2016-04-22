#ifndef CONVERTER_H
#define CONVERTER_H

#include <boost/mpl/map.hpp>

#include <armadillo>

using namespace arma;

namespace mpl = boost::mpl;

namespace AnalysisCore{
  namespace internal{
  
    template<class T>
    struct Converter{
      typedef T type;
    };
    
    struct VectorConverter : public Converter<vec>{
      
      template<class AT> double* Get(vec* v, AT* num_rows){
        *num_rows = v->n_rows;
        return v->memptr();
      }
      
      template<class AT> void Set(vec* v, double* ptr, AT num_rows){
        *v = vec(ptr, num_rows);
      }
      
    };
    
    struct MatrixConverter : public Converter<mat>{
      
      template <class AT1, class AT2> double* Get(vec* v, AT1* num_rows, AT2* num_cols){
        *num_rows = v->n_rows;
        *num_cols = v->n_cols;
        return v->memptr();
      }
      
      template <class AT1, class AT2> void Set(vec* v, double* ptr, AT1 num_rows, AT2 num_cols){
        *v = vec(ptr, num_rows, num_cols);
      }
      
    };
  
    typedef mpl::map<
          mpl::pair<vec, VectorConverter>,
          mpl::pair<mat, MatrixConverter>
          > Converters;
    
  }    
}

#endif //CONVERTER_H