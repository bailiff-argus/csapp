//               %rdi     %xmm0    %rsi       %rdx
double funct3(int *ap, double b, long c, float *dp) {
  double a = *ap;
  float d = *dp;
  if (b > a)
    return d * c;
  else
    return 2*d + c;
}
