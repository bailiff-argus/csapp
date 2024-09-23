#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

// return 1 when x can be represented as an n-bit, 2's-complement number;
// 0 otherwise; 1 <= n <= w

int fits_bits(int x, int n) {
  return (n == sizeof(int) << 3) || ((x & (~0x00u << n)) == 0);
}

int main(void) {
  uint x, n, repr, fits;
  for (int i = 0; i < 100000000; i++) {
    x = rand();
    n = rand() % (sizeof(uint) << 3) + 1;

    repr = (n == (sizeof(uint) << 3)) ? (1) : (x <= ((0x01u << n) - 1));
    fits = fits_bits(x, n);

    if (repr != fits_bits(x, n)) {
      printf("x=%.8X, n=%d, r=%d, f=%d\n", x, n, repr, fits_bits(x, n));
    }
  }

  return 0;
}
