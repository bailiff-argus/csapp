#include <complex.h>

// A. Complex values are spread across two neighbouring registers, real part occupying the lower register, and imaginary -- the upper one.
//    (xmm0, xmm1), (xmm2, xmm3), (xmm4, xmm5), ...
// B. They're returned as imaginary part in xmm1 and real in xmm0.

double c_imag(double complex x) {
  return cimag(x);
}

double c_real(double complex x) {
  return creal(x);
}

double complex c_sub(double complex x, double complex y) {
  return x - y;
}
