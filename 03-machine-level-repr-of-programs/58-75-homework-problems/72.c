#include <alloca.h>

//            %rdi      %rsi     %rdx
long aframe(long n, long idx, long *q) {
  long i;
  long **p = alloca(n * sizeof(long *));
  p[0] = &i;
  for (i = 1; i < n; i++)
    p[i] = q;
  return *p[idx];
}
