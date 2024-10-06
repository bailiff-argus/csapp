#define val1 (d)
#define val2 (i)
#define val3 (l)
#define val4 (f)

double fcvt2(int *ip, float *fp, double *dp, long l) {
  int i = *ip;
  float f = *fp;
  double d = *dp;

  *ip = (int)     val1;
  *fp = (float)   val2;
  *dp = (double)  val3;

  return (double) val4;
}

#undef val1
#undef val2
#undef val3
#undef val4
