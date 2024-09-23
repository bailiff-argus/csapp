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

unsigned srl(unsigned x, int k) {
  unsigned xsra = (int)x >> k;
  int num_of_bits = sizeof(int) << 3;
  unsigned mask = ~(~0 << (num_of_bits - k)); // 0...01...1
  return xsra & mask;
}

unsigned sra(int x, int k) {
  int xsrl, num_of_bits, sig, neg;
  unsigned mask;

  xsrl = (unsigned)x >> k;
  num_of_bits = sizeof(int) << 3;
  sig = (0x01 << (num_of_bits - 1));
  neg = (sig & x) != 0;
  mask = (-neg) << (num_of_bits - k); // 1...10...0

  return xsrl | mask;
}

int main(void) {
  uint x = 0x12345678, k = 16, rsrl = srl(x, k), rsra = sra(x, k);
  printf("\n");
  printf("x =        0x%.8X\n", x);
  printf("srl x %d = 0x%.8X\n", k, rsrl);
  printf("sra x %d = 0x%.8X\n", k, rsra);
  return 0;
}
