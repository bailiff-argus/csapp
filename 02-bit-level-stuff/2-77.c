#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

int32_t signed_high_prod(int32_t x, int32_t y) {
  int64_t mul = (int64_t)x * y;
  return mul >> 32;
}

uint32_t unsigned_high_prod(uint32_t x, uint32_t y) {
  int32_t x_sign = x >> 31, y_sign = y >> 31;
  return signed_high_prod(x, y) + x_sign * y + y_sign * x;
}
