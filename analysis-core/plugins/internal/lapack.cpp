#include "internal/lapack.h"

#include <algorithm>

using AnalysisCore::LAPACK;

extern "C" void dgeqrf_(int* m,
                   int* n,
                   double* a,
                   int* lda,
                   double* tau,
                   double* work,
                   int* lwork,
                   int* info);

extern "C" void dormqr_(char* side,
                   char* trans,
                   int* m,
                   int* n,
                   int* k,
                   double* a,
                   int* lda,
                   double* tau,
                   double* c,
                   int* ldc,
                   double* work,
                   int* lwork,
                   int* info);

int LAPACK::GetResidualsUsingQR(int num_rows_a, int num_cols_a, int num_rows_b, int num_cols_b, double* A, double* b)
{
  //double* mutable_a = const_cast<double*>(A);
  //double* mutable_b = const_cast<double*>(b);
  
  int lwork = std::max(1, num_cols_a);
  double* work = new double[lwork];
  
  double* tau = new double[std::min(num_rows_a, num_cols_a)];
  
  int info;
  
  dgeqrf_(&num_rows_a, &num_cols_a, A, &num_rows_a, tau, work, &lwork, &info);
  
  if(info < 0){
    delete[] work;
    return info;
  }
  
  delete[] work;
  
  char side = 'L';
  char trans = 'T';
  
  lwork = std::max(1, num_cols_b);
  work = new double[lwork];
  
  int k = std::min(num_rows_a, num_cols_a);
  
  dormqr_(&side, &trans, &num_rows_b, &num_cols_b, &k, A, &num_rows_b, tau, b, &num_rows_b, work, &lwork, &info);
  
  if(info < 0){
    delete[] work;
    return info;
  }
  
  for(int i = 0; i < num_cols_a; ++i)
    b[i] = 0;
  
  trans = 'N';
  
  dormqr_(&side, &trans, &num_rows_b, &num_cols_b, &k, A, &num_rows_b, tau, b, &num_rows_b, work, &lwork, &info);
  
  delete[] work;
  
  return info;
}
