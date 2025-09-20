#include <poly.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POLY_DEGREE 100000000
// #define POLY_DEGREE 100

#define X 1.000001

static double randbetween(double min, double max) {
  double range = (max - min);
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

static double *mk_poly_coefficients(long degree) {
  double *coeffs = malloc((degree + 1) * sizeof(double));
  if (coeffs == NULL)
    return NULL;

  for (long i = 0; i <= degree; i++) {
    coeffs[i] = randbetween(-10.0, 11.0);
  }

  return coeffs;
}

static void print_test_result(const char *func, uint64_t cycles,
                              double result) {
  printf("%35s: CPE %5.2lf; result %e\n", func,
         cycles / (double)(POLY_DEGREE + 1), result);
}

static inline uint64_t rdtsc(void) {
  uint32_t hi, lo;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)lo) | (((uint64_t)hi) << 32);
}

int main(void) {
  uint64_t start, end;
  double *coeffs;
  double result;

  srand(time(NULL));

  coeffs = mk_poly_coefficients(POLY_DEGREE);
  if (coeffs == NULL) {
    perror("malloc: ");
    return 1;
  }

#define test_poly_sum(func)                                                    \
  do {                                                                         \
    start = rdtsc();                                                           \
    result = func(coeffs, X, POLY_DEGREE);                                     \
    end = rdtsc();                                                             \
    print_test_result(#func, end - start, result);                             \
  } while (0)

  test_poly_sum(poly_sum_scalar_naive);
  test_poly_sum(poly_sum_scalar_horner_naive);
  test_poly_sum(poly_sum_scalar_horner_4x4);
  test_poly_sum(poly_sum_scalar_horner_4x1a);
  test_poly_sum(poly_sum_vector_naive);
  test_poly_sum(poly_sum_vector_horner_4x4);
  test_poly_sum(poly_sum_vector_horner_16x16);
  test_poly_sum(poly_sum_vector_horner_64x16a);

#undef test_poly_sum
  free(coeffs);
  return 0;
}
