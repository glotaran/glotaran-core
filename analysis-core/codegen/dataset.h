#ifndef DATASET_H
#define DATASET_H

#include <armadillo>

#include "analysis-core_export.h"

using namespace arma;

namespace ac{
  
  class ANALYSIS_CORE_EXPORT Dataset{

  public:
    Dataset(int id);
    
    /*[[[cog
    import cog
    from dataset import *
    for name in names:
      cog.outl('{0}& Get{1}();'.format(type, name.capitalize()))
      cog.outl('{0} Get{1}(int* num_rows, int* num_cols);'.format(atype, name.capitalize()))
      cog.outl('void Set{0}({1}& {2});'.format(name.capitalize(), type, name))
      cog.outl('void Set{0}({1} {2}, int num_rows, int num_cols);'.format(name.capitalize(), atype, name))
      cog.outl()
    ]]]*/
    //[[[end]]]
  private:
    int id_;
    
    /*[[[cog
    for name in names:
      cog.outl('{0} {1}_;'.format(type, name))
    cog.outl()
    ]]]*/
    //[[[end]]]
  };
  
}

#ifdef __cplusplus
extern "C" {
#endif
  
  /*[[[cog
    for name in names:
      cog.outl('ANALYSIS_CORE_EXPORT {0} ac_{2}_get_{1}(void* {2}, int* num_rows, int* num_cols);'.format(atype, name, classname))
      cog.outl('ANALYSIS_CORE_EXPORT void ac_{1}_set_{0}(void* {1}, {2} {0}, int num_rows, int num_cols);'.format(name, classname, atype))
      cog.outl('')
    ]]]*/
    //[[[end]]]
    
#ifdef __cplusplus
}
#endif

#endif // DATASET_H
