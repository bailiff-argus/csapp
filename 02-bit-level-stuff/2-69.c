#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast

// Do rotating left shift, assume 0 <= n < w;
uint rotate_left(uint x, int n) {
  uint left_half, right_half;
  int w = sizeof(uint) << 3;

  left_half = x << n;
  /*right_half = x >> (w - n);*/
  right_half = (x >> (w - n - 1)) >> 1;
  return left_half | right_half;
}

int main(void) {
  uint x = 0x12345678;
  for (int i = 0; i < sizeof(int) << 3; i++) {
    printf("n = %2d -> mask = %.8X\n", i, rotate_left(x, i));
  }

  return 0;
}
