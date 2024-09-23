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

typedef uint32_t packed_t;

int xbyte(packed_t word, int bytenum) {
  return (int)(word << ((3 - bytenum) << 3)) >> 24;
}

int main(void) {
  packed_t word = 0xAF000000;
  int bytenum = 3, res = xbyte(word, bytenum);

  printf("%.8X, %.8X, %d\n", word, res, res);
  return 0;
}
