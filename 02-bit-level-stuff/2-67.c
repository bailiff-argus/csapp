// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast
//
// w = 32

#include <stdint.h>
#include <stdio.h>

int bad_int_size_is_32() {
  int set_msb, beyond_msb;

  set_msb = 1 << 31;
  beyond_msb = 1 << 32;

  return set_msb && !beyond_msb;
}

int ok32_int_size_is_32() {
  int set_msb, beyond_msb;

  set_msb = 1 << 31;
  beyond_msb = set_msb << 1;

  return set_msb && !beyond_msb;
}

int ok16_int_size_is_32() {
  int set_msb, beyond_msb;

  set_msb = 1 << 15;
  set_msb <<= 15;
  set_msb <<= 1;
  beyond_msb = set_msb < 1;

  return set_msb && !beyond_msb;
}
