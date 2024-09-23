#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

int divide_power2(int x, int k) {
  int sign = !!(INT_MIN & x);
  return (x + (sign << k) - sign) >> k;
}

int threefourths(int x) {
  int residual_mask, main, residual, sign;

  residual_mask = 0x03; // 0...011

  main = x & ~residual_mask;    // X...X00: everything but the last 2 bits
  residual = x & residual_mask; // 0...0XX: the last 2 bits

  // x = m + r
  // 3/4 * (x) = 3/4 * (m + r) = (m / 4) * 3 + (r * 3) / 4

  // main is safe to just right shift, since the right two bits are 0
  main = main >> 2; // main / 4
  main = (main << 2) - main;

  // residual is definitely positive, BUT we must
  // round it UP if x is NEGATIVE, and round it DOWN if the x is POSITIVE
  // since overall rounding must be towards zero, which means that we want
  // to increase the negative number, and decrease the positive

  sign = !!(INT_MIN & x);
  residual = (residual << 2) - residual;
  residual = (residual + (sign << 2) - sign) >> 2;

  return main + residual;
}
