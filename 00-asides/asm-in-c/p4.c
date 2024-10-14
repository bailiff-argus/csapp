#include <stdio.h>

int odd_parity_asm(unsigned long x) {
  unsigned char result = 0;

  asm(
    "test %[x],  %[x]     \n\t"
    "jz   .end            \n\t"
    ".start:              \n\t"
    "setnp %%bl           \n\t"
    "xor   %%bl, %[result]\n\t"
    "shr   $8,   %[x]     \n\t"
    "jnz   .start         \n\t"
    ".end:"
    : [result] "+r" (result)
    : [x] "r" (x)
    : "%bl"
  );

  return (int) result;
}

int odd_parity(unsigned long x) {
  unsigned char result = 0;

  while (x != 0) {
    unsigned char temp_res = 0, bx = x & 0xFF;

    asm(
      "testb  %[bx], %[bx]     \n\t"
      "setnp  %[temp_res]     \n\t"
      : [temp_res] "=r" (temp_res)
      : [bx] "r" (bx)
    );

    result ^= temp_res;
    x = x >> 8;
  }

  return (int) result;
}

int main(void) {
  unsigned long nums[]   = {0, 1, 2, 3, 0x1000, 0x1001};
  int           parity[] = {0, 1, 1, 0,      1,      0};
  for (unsigned long i = 0; i < sizeof(nums) / sizeof(*nums); i++) {
    printf("%lu: (a) %d vs (ca) %d vs %d\n", nums[i], odd_parity_asm(nums[i]), odd_parity(nums[i]), parity[i]);
  }
}
