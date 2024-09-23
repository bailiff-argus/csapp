#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// No == or !=
// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast

int not_zero(int x) {
  return !!x;
}

int any_bit_is_1(int x) {
  return not_zero(x);
}

int any_bit_is_0(int x) {
  return not_zero(x ^ ~0);
}

int any_bit_in_lsb_is_1(int x) {
  int lsb = x & 0xFF;
  return any_bit_is_1(lsb);
}

int any_bit_in_msb_is_0(int x) {
  int num_of_bits = sizeof(x) << 3;
  int msb = (x >> (num_of_bits - 1)) & 0xFF;
  return any_bit_is_0(x);
}

int main(void) {
  for (unsigned x = 0; x <= UINT32_MAX; x += 10) {
  }

  return 0;
}
