#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

double dsqrt(double x) {
  double ret = 0;

  asm(
    "sqrtsd  %[x], %[r]"
    : [r] "=x" (ret)
    : [x] "x" (x)
  );

  return ret;
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
  float_bits num = {0}, res_asm, res_naive;

  srand(time(NULL));

  // >> 6 to make it finish quickly
  for (size_t i = 0; i < (UINT32_MAX >> 6); i++) {
    num.fb = get_random_u64();

    res_asm.f = dsqrt(num.f);
    res_naive.f = sqrt(num.f);

    if (res_asm.fb != res_naive.fb) {
      printf("%e => asm:%e vs naive:%e\n", num.f, res_asm.f, res_naive.f);
      return 1;
    }
  }

  return 0;
}
