#include <stdint.h>
#include <stdio.h>

// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast

// Mask with least significant n bits set to 1.
// E.g.: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
// 1 <= n <= w

int lower_one_mask(int n) {
  return (0x02 << (n - 1)) - 1;
}

int main(void) {
  for (int i = 1; i <= sizeof(int) << 3; i++) {
    printf("n = %2d -> mask = %.8X\n", i, lower_one_mask(i));
  }

  return 0;
}
