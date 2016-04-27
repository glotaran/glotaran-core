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
      
      double* Get(vec& v, int* num_rows){
        *num_rows = v.n_rows;
        return v.memptr();
      }
      
      void Set(vec& v, double* ptr, int num_rows){
        v = vec(ptr, num_rows);
      }
      
    };
    
    struct MatrixConverter : public Converter<mat>{
      
      double* Get(mat& m, int* num_rows, int* num_cols){
        *num_rows = m.n_rows;
        *num_cols = m.n_cols;
        return m.memptr();
      }
      
      void Set(mat& m, double* ptr, int num_rows, int num_cols){
        m = mat(ptr, num_rows, num_cols);
      }
      
    };
  
    typedef mpl::map<
          mpl::pair<vec, VectorConverter>,
          mpl::pair<mat, MatrixConverter>
          > Converters;
    
  }    
}

#endif //CONVERTER_H