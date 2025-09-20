#include <assert.h>
#include <stddef.h>
#include <stdio.h>

double poly_sum_scalar_naive(double a[], double x, long degree) {

  /*
   * Calculate the polynomial directly:
   *   a_0 + a_1 * x + a_2 * x^2 + a_3 * x^3 + ...
   */

  long i;

  double xpwr = x;
  double result = a[0];

  for (i = 1; i <= degree; i++) {
    result += a[i] * xpwr;
    xpwr *= x;
  }

  return result;
}

double poly_sum_scalar_horner_naive(double a[], double x, long degree) {

  /*
   * Horner's method is to rearrange the polynomial and calculate from inside
   * out:
   *   a_0 + x(a_1 + x(a_2 + x(a_3 + x(...))))
   */

  long i;

  double result = a[degree];

  for (i = degree - 1; i >= 0; i--) {
    result = a[i] + x * result;
  }

  return result;
}

double poly_sum_scalar_horner_4x4(double a[], double x, long degree) {

  /*
   * Idea:
   *
   *   a0 + x(a1 + x(a2 + x(a3 + x(...))))
   *
   * can be broken down into a set of N accumulators, and each is calculated
   * with a step x^N:
   *
   * acc_0   =     1 (a_0 + x^N(a_N + x^N(a_2N + x^N(a_3N ... ))))
   * acc_1   =     x (a_1 + x^N(a_N+1 + x^N(a_2N+1 + x^N(a_3N+1 ... ))))
   * ...
   * acc_N-1 = x^N-1 (a_N-1 + x^N(a_2N-1 + x^N(a_3N-1 + x^N(a_4N-1 ... ))))
   *
   * result = sum(i=0,N-1) acc_i
   */

  long i = degree;

  double result, accum0 = 0, accum1 = 0, accum2 = 0, accum3 = 0;

  double x2 = x * x, x3 = x2 * x, x4 = x2 * x2;

  for (i = degree; i >= 3; i -= 4) {
    double a0 = a[i], a1 = a[i - 1], a2 = a[i - 2], a3 = a[i - 3];

    accum0 = a0 + x4 * accum0;
    accum1 = a1 + x4 * accum1;
    accum2 = a2 + x4 * accum2;
    accum3 = a3 + x4 * accum3;
  }

  result = (x3 * accum0 + x2 * accum1) + (x * accum2 + accum3);
  while (i >= 0)
    result = a[i--] + x * result;

  return result;
}

double poly_sum_scalar_horner_4x1a(double a[], double x, long degree) {

  /*
   * Idea:
   *
   * take multiple elements at once and expand them as a single polynomial,
   * then order the calculations in a way that reduces data dependencies.
   *
   *     a_k + x(a_k+1 + x(a_k+2 + x(a_k+3 + x*A))) =
   *   = a_k + a_k+1 * x + a_k+2 * x^2 + a_k+3 * x^3 + A * x^4 =
   *   = ((a_k + a_k+1 * x) + (a_k+2 * x^2 + a_k+3 * x^3)) + A * x^4
   *
   */

  long i = degree;

  double result = a[degree];

  double x2 = x * x;
  double x3 = x * x2;
  double x4 = x2 * x2;

  for (i = degree-1; i >= 3; i -= 4) {
    double a3 = a[i], a2 = a[i - 1], a1 = a[i - 2], a0 = a[i - 3];
    result = ((a0 + a1 * x) + (a2 * x2 + a3 * x3)) + (result * x4);
  }

  while (i >= 0)
    result = a[i--] + x * result;

  return result;
}

/*
 * Double vector for load into YMMs.
 * ! It's important to pay attention to memory alignment.
 *   If it's 32 bytes, a segmentation fault may occur.
 */

#define VBYTES 32
#define VSIZE (VBYTES / sizeof(double))
typedef double dvec_t __attribute__((vector_size(VBYTES)));

#define get_chunk(from, offs) *((dvec_t *)from + offs)

double poly_sum_vector_naive(double a[], double x, long degree) {

  /*
   * This is just a poly_sum_scalar_naive, unrolled for SIMD support.
   */

  long i;
  long cnt = degree + 1;

  double xpwr = 1.0;
  double result = 0;

  dvec_t accum;
  dvec_t xV, xpwr_v;

  for (i = 0; i < VSIZE; i++) {
    accum[i] = 0;
    xpwr *= x;
  }

  for (i = 0; i < VSIZE; i++) {
    xV[i] = xpwr;
  }

  xpwr = 1.0;
  while (cnt && ((size_t)a % VBYTES)) {
    result += *a++ * xpwr;
    xpwr *= x;
    cnt--;
  }

  xpwr_v[0] = xpwr;
  for (i = 1; i < VSIZE; i++) {
    xpwr_v[i] = xpwr_v[i-1] * x;
  }

  while (cnt >= VSIZE) {
    dvec_t chunk = get_chunk(a, 0);

    accum += chunk * xpwr_v;
    xpwr_v *= xV;

    a += VSIZE;
    cnt -= VSIZE;
  }

  xpwr = xpwr_v[0];
  while (cnt) {
    result += *a++ * xpwr;
    xpwr *= x;
    cnt--;
  }

  for (i = 0; i < VSIZE; i++)
    result += accum[i];

  return result;
}

double poly_sum_vector_horner_4x4(double a[], double x, long degree) {

  /*
   * This is a copy of poly_sum_scalar_horner_4x4, but adapted for SIMD.
   */

  long i = degree, j;

  double result = 0.0;
  double xpwr = 1.0;

  dvec_t accum, Vx, Vn;

  for (j = 0; j < VSIZE; j++) {
    accum[j] = 0;
    Vn[j] = xpwr;
    xpwr *= x;
  }

  for (j = 0; j < VSIZE; j++)
    Vx[j] = xpwr;

  while (((size_t)&a[i + 1] % VBYTES) && (i >= 0)) {
    result = a[i] + result * x;
    i--;
  }

  accum[VSIZE-1] = result;
  for (; i >= (long)(VSIZE - 1); i -= VSIZE) {
    dvec_t a_chunk = get_chunk(&a[i - (VSIZE - 1)], 0);
    accum = a_chunk + Vx * accum;
  }

  accum = accum * Vn;

  result = 0.0;
  for (j = 0; j < VSIZE; j++)
    result += accum[j];

  while (i >= 0)
    result = a[i--] + x * result;

  return result;
}

#define ACCUMULATOR_COUNT 4

double poly_sum_vector_horner_16x16(double a[], double x, long degree) {

  /*
   * We're increasing the number of accumulators to 4.
   * NOTE that accumulator count is often hardcoded, like in accumX variables.
   */

  long i = degree, j;

  double result = 0.0;
  double xpwr_vsize = 1.0, xpwr_total = 1.0;

  dvec_t Vxt, Vxs, Vn;

  dvec_t accum1, accum2, accum3, accum4, accum;

  for (j = 0; j < VSIZE; j++) {
    accum[j] = 0;

    accum1[j] = 0;
    accum2[j] = 0;
    accum3[j] = 0;
    accum4[j] = 0;

    Vn[j] = xpwr_vsize;
    xpwr_vsize *= x;
  }

  xpwr_total = 1.0;
  for (j = 0; j < ACCUMULATOR_COUNT; j++)
    xpwr_total *= xpwr_vsize;

  for (j = 0; j < VSIZE; j++) {
    Vxt[j] = xpwr_total;
    Vxs[j] = xpwr_vsize;
  }

  while (((size_t)&a[i + 1] % VBYTES) && (i >= 0)) {
    result = a[i] + result * x;
    i--;
  }

  accum4[VSIZE-1] = result;
  for (; i >= (long)(ACCUMULATOR_COUNT * VSIZE - 1); i -= ACCUMULATOR_COUNT * VSIZE) {
    const double *mem = &a[i - (VSIZE * ACCUMULATOR_COUNT - 1)];

    dvec_t
      a_chunk1 = get_chunk(mem, 0),
      a_chunk2 = get_chunk(mem, 1),
      a_chunk3 = get_chunk(mem, 2),
      a_chunk4 = get_chunk(mem, 3);

    accum1 = a_chunk1 + Vxt * accum1;
    accum2 = a_chunk2 + Vxt * accum2;
    accum3 = a_chunk3 + Vxt * accum3;
    accum4 = a_chunk4 + Vxt * accum4;
  }

  accum += accum1 * Vn; Vn *= Vxs;
  accum += accum2 * Vn; Vn *= Vxs;
  accum += accum3 * Vn; Vn *= Vxs;
  accum += accum4 * Vn;

  result = 0.0;
  for (j = 0; j < VSIZE; j++)
    result += accum[j];

  while (i >= 0)
    result = a[i--] + x * result;

  return result;
}

#define EXPANSION_ORDER 4

/*
 * Note that this version actually performs worse than the previous.
 */

double poly_sum_vector_horner_64x16a(double a[], double x, long degree) {

  /*
   * And now we attempt the final performance upgrade, expanding each expression
   * like in poly_sum_scalar_horner_4x1a.
   */

  long i = degree, j;

  double result = 0.0;
  double xpwr_vsize = 1.0, xpwr_total = 1.0;

  dvec_t Vxt, Vxt2, Vxt3, Vxt4, Vxs, Vn;

  dvec_t accum0, accum1, accum2, accum3, accum;

  for (j = 0; j < VSIZE; j++) {
    accum[j] = 0;

    accum0[j] = 0;
    accum1[j] = 0;
    accum2[j] = 0;
    accum3[j] = 0;

    Vn[j] = xpwr_vsize;
    xpwr_vsize *= x;
  }

  xpwr_total = 1.0;
  for (j = 0; j < ACCUMULATOR_COUNT; j++)
    xpwr_total *= xpwr_vsize;

  for (j = 0; j < VSIZE; j++) {
    Vxt[j] = xpwr_total;
    Vxs[j] = xpwr_vsize;
  }

  Vxt2 = Vxt * Vxt;
  Vxt3 = Vxt2 * Vxt;
  Vxt4 = Vxt2 * Vxt2;

  while (((size_t)&a[i + 1] % VBYTES) && (i >= 0)) {
    result = a[i] + result * x;
    i--;
  }

  accum3[VSIZE-1] = result;
  for (; i >= (long)(EXPANSION_ORDER * ACCUMULATOR_COUNT * VSIZE - 1); i -= EXPANSION_ORDER * ACCUMULATOR_COUNT * VSIZE) {
    const double *mem = &a[i - (VSIZE * ACCUMULATOR_COUNT * EXPANSION_ORDER - 1)];

#define fill_accum(no)                                                         \
  do {                                                                         \
    dvec_t a_chunk0 = get_chunk(mem, 0 + no),                                  \
           a_chunk1 = get_chunk(mem, 4 + no),                                  \
           a_chunk2 = get_chunk(mem, 8 + no),                                  \
           a_chunk3 = get_chunk(mem, 12 + no);                                 \
                                                                               \
    accum##no =                                                                \
        ((a_chunk0 + a_chunk1 * Vxt) + (a_chunk2 * Vxt2 + a_chunk3 * Vxt3)) +  \
        Vxt4 * accum##no;                                                      \
  } while (0)

    fill_accum(0);
    fill_accum(1);
    fill_accum(2);
    fill_accum(3);

#undef fill_accum
  }

  accum += accum0 * Vn; Vn *= Vxs;
  accum += accum1 * Vn; Vn *= Vxs;
  accum += accum2 * Vn; Vn *= Vxs;
  accum += accum3 * Vn;

  result = 0.0;
  for (j = 0; j < VSIZE; j++)
    result += accum[j];

  while (i >= 0)
    result = a[i--] + x * result;

  return result;
}
