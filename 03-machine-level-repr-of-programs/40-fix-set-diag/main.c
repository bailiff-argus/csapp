#define N 16
typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val) {
  long i;
  for (i = 0; i < N; i++)
    A[i][i] = val;
}

void fix_set_diag_opt(fix_matrix A, int val) {
  int *Aptr = &A[0][0];

  // we expect to fill in N values, which means (N - 1) jumps
  // after jump N, we should stop
  for (int i = 0; i != N * (N + 1); i += (N + 1))
    Aptr[i] = val;
}
