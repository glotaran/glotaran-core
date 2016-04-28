#ifndef LAPACK_H
#define LAPACK_H
namespace AnalysisCore{
  
  class LAPACK
  {
  public:
    static int GetResidualsUsingQR(int num_rows_a, int num_cols_a, int num_rows_b, int num_cols_b, double* A, double* b);
  };
  
}

#endif // LAPACK_H
