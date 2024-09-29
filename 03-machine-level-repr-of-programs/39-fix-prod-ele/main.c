// For T D[R][C], sizeof(T) = L:
// &D[i][j] = Xd + L(C*i + j)

#define N 16
typedef int fix_matrix[N][N];

//                           %rdi          %rsi    %rdx    %rcx
int fix_prod_ele_opt(fix_matrix A, fix_matrix B, long i, long k) {
  int *Aptr = &A[i][0]; // Aptr = &(M[Xa + L(N*i + 0)]) = Xa + L * N * i
  int *Bptr = &B[0][k]; // Bptr = &(M[Xb + L(N*0 + k)]) = Xb + L * k
  int *Bend = &B[N][k]; // Bend = &(M[Xb + L(N*N + k)]) = Xb + L * N * N + k
  int result = 0;

  do {
    result += *Aptr * *Bptr;
    Aptr++;
    Bptr += N;
  } while (Bptr != Bend);

  return result;
}
