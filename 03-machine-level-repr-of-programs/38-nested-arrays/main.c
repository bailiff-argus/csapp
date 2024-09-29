#define M 5
#define N 7

long P[M][N];
long Q[N][M];

//                 %rdi    %rsi
long sum_element(long i, long j) {
  return P[i][j] + Q[j][i];
}
