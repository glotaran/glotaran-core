#include <memory>

#include "analysis-core/dataset.h"

using namespace ac;

Dataset::Dataset(int id) : id_(id){

}

/*[[[cog
import cog
from dataset import *
for name in names:
  cog.outl('{0}& {1}::Get{2}'.format(type, classname.capitalize(), name.capitalize()) + '(){')
  cog.outl('  return {0}_;'.format(name))
  cog.outl('}')
  cog.outl()
  cog.outl('{0} {1}::Get{2}'.format(atype, classname.capitalize(), name.capitalize()) + '(int* num_rows, int* num_cols){')
  cog.outl('  *num_rows = {0}_.n_rows;'.format(name))
  cog.outl('  *num_cols = {0}_.n_cols;'.format(name))
  cog.outl('  return {0}_.memptr();'.format(name))
  cog.outl('}')
  cog.outl()
  cog.outl('void {0}::Set{1}'.format(classname.capitalize(), name.capitalize()) + '({0}& {1}){{'.format(type, name))
  cog.outl('  {0}_ = {0};'.format(name))
  cog.outl('}')
  cog.outl()
  cog.outl('void {0}::Set{1}'.format(classname.capitalize(), name.capitalize()) + '({0} {1}, int num_rows, int num_cols){{'.format(atype, name))
  cog.outl('  {0}_ = {1}({0}, num_rows, num_cols);'.format(name, type, name))
  cog.outl('}')
  cog.outl()
]]]*/
//[[[end]]]

/*[[[cog
    for name in names:
      cog.outl('{0} ac_{2}_get_{1}(void* {2}, int* num_rows, int* num_cols){{'.format(atype, name, classname))
      cog.outl('  auto d = reinterpret_cast<std::shared_ptr<{0}>*>({1});'.format(classname.capitalize(), classname))
      cog.outl('  return (*d)->Get{0}(num_rows, num_cols);'.format(name.capitalize()))
      cog.outl('}')
      cog.outl('')
      cog.outl('void ac_{1}_set_{0}(void* {1}, {2} {0}, int num_rows, int num_cols){{'.format(name, classname, atype))
      cog.outl('  auto d = reinterpret_cast<std::shared_ptr<{0}>*>({1});'.format(classname.capitalize(), classname))
      cog.outl('  (*d)->Set{0}({1}, num_rows, num_cols);'.format(name.capitalize(), name))
      cog.outl('}')
      cog.outl('')
]]]*/
//[[[end]]]