#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

int divide_power2(int x, int k) {
  int sign = !!(INT_MIN & x);
  return (x + (sign << k) - sign) >> k;
}
