#ifndef LAPACK_H
#define LAPACK_H

class LAPACK
{
public:
  static int GetResidualsUsingQR(int num_rows_a, int num_cols_a, int num_rows_b, int num_cols_b, const double* A, const double* b, int* num_rows_res, int* num_cols_res, double* res);
};

#endif // LAPACK_H
