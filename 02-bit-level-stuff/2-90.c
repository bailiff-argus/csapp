#include <sys/types.h>

float u2f(uint u) {
  return *((float *)&u);
}

float fpwr2(int x) {
  // return 2 ** x
  uint exp, frac, u;

  // assuming float32, s = 1, k = 8, n = 23, bias = 127
  // normalized: E in [-126, +127]; M in [1, 2) -> m = 1 -> f = 0
  // denormalized: E = -126; M in [2^-23, 1-2^-23]

  if (x < -149) {
    // too small, return 0.0
    exp = 0;
    frac = 0;
  } else if (x < -126) {
    // denormalized: 2 ^ (-23 ... -1) * 2^(-126) -> [-149, -127]
    exp = 0;
    frac = 1 << (x + 149);
  } else if (x < 128) {
    exp = x + 127;
    frac = 0;
  } else {
    // too large, return +inf
    exp = ~0;
    frac = 0;
  }

  u = exp << 23 | frac;
  return u2f(u);
}
