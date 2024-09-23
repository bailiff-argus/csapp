#include <stdint.h>

void decode1(long *xp, long *yp, long *zp) {
  uint64_t x = *xp, y = *yp, z = *zp;

  *yp = x;
  *zp = y;
  *xp = z;
}
