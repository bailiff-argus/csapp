#include <sys/types.h>

uint f2u(float x) {
  return *((uint *)&x);
};

int float_le(float x, float y) {
  uint ux = f2u(x), uy = f2u(y);
  uint sx = ux >> 31, sy = uy >> 31;

  return (sx != sy) ? (sx || (ux == 0) && (uy << 1 == 0))
                    : ((ux == uy) || ((ux < uy) ^ sx));
}
