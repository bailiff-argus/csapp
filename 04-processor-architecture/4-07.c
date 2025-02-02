#include <stdint.h>
#include <stdio.h>

int main(void) {
  int64_t x;

  asm(
    "movq %%rsp,   %[x]\n\t"
    "pusq %%rsp\n\t"
    "popq %%rdx\n\t"
    "subq %%rdx,   %[x]"
    : [x] "=r" (x)
    :
    : "%rdx"
  );

  printf("%ld\n", x); // the result is zero
  // this implies that first the data is written,
  // and then the stack pointer is decremented

  return 0;
}
