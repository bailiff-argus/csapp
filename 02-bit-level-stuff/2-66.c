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
// at most 15 arithmetic, bitwise and logical operations

// return 1 if the bit level representation contains an odd number of 1s
#include <stdint.h>
#include <stdio.h>

// Generate mask indicating leftmost 1 in x.
// For example, 0xFF00 -> 0x8000, 0x6600 -> 0x4000.
// x = 0 -> return 0

// + - ! == != & | ^ << >>, AT MOST 15 ARITHMETIC, BITWISE, AND LOGICAL OPS
int32_t leftmost_one(uint32_t x) {
  // the idea is to fill everything to the right of x's MSBit with 1s, excluding
  // that bit, inverse it, and use it as a mask to capture only the most
  // significant bit
  uint32_t not_mask, mask;

  not_mask = x >> 1; // op. 1, at least 1/31 bits filled;
                     // guaranteed 0 on x's MSB since uint shifts are logical

  // since we're excluding the MSB and everything to the left of it, we're
  // filling up at most 31 bits
  not_mask |= not_mask >> 1;  // op. 2 &  3, at least 2/31 bits filled
  not_mask |= not_mask >> 2;  // op. 4 &  5, at least 4/31 bits filled
  not_mask |= not_mask >> 4;  // op. 6 &  7, at least 8/31 bits filled
  not_mask |= not_mask >> 8;  // op. 8 &  9, at least 16/31 bits filled
  not_mask |= not_mask >> 16; // op.10 & 11,          31/31 bits filled

  mask = ~not_mask; // op.12, has all the most significant bits on the left
                    // filled, up to and including x's most significant bit

  return x & mask; // op.13
}

int main(void) {
  uint32_t x = 0xABCDABCD;
  printf("x = 0x%.8X\nmsb=0x%.8X\n", x, leftmost_one(x));
  return 0;
}
