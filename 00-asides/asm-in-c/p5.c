#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

double dmin(double x, double y) {
  double ret = 0;
  asm(
    "vminsd %[x], %[y], %[r]"
    : [r] "=x" (ret)
    : [x] "x" (x), [y] "x" (y)
    );

  return ret;
}

double dmin_naive(double x, double y) {
  return (x >= y) ? y : x;
}

typedef union {
  uint64_t fb;
  double f;
} float_bits;

static uint64_t get_random_u64(void) {
  uint64_t res = 0;
  for (size_t i = 0; i < 5; i++)
    res = (res << 15) | (rand() & 0x7FFF);
  return res;
}

int main(void) {
  float_bits num1 = {0}, num2 = {0}, res_asm, res_naive;

  srand(time(NULL));

  // >> 6 to make it finish quickly
  for (size_t i = 0; i < (UINT32_MAX >> 6); i++) {
    num1.fb = get_random_u64();
    num2.fb = get_random_u64();

    res_asm.f = dmin(num1.f, num2.f);
    res_naive.f = dmin_naive(num1.f, num2.f);

    if (res_asm.fb != res_naive.fb) {
      printf("%e and %e => asm:%e vs naive:%e\n", num1.f, num2.f, res_asm.f, res_naive.f);
      return 1;
    }
  }

  return 0;
}
