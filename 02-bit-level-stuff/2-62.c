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

#define TYPE unsigned int

int int_shifts_are_arithmetic(void) {
  TYPE x = ~0;
  printf("x = %x\n", x);

  TYPE last_bit = x >> ((sizeof(x) << 3) - 1);
  printf("lb= %.8x\n", last_bit);

  return ((x >> ((sizeof(int) << 3) - 1)) & 0x02) >> 1;
}

int main(void) {
  printf("shifts are arithmetic: %d\n", int_shifts_are_arithmetic());
  return 0;
}
