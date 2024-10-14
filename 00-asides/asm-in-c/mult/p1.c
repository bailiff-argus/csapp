//                 %rdi    %rsi        %rdx
int tmult_ok_asm(long x, long y, long *dest) {
  unsigned char result;
  *dest = x * y;

  asm("setae  %[b] \n\t"
      : [b] "=r" (result)
      );

  return (int) result;
}

int umult_ok(unsigned long x, unsigned long y, unsigned long *dest) {
  unsigned char result;

  asm("movq   %[x], %%rax\n\t"
      "mult   %[y]\n\t"
      "movq   %%rax, %[p]"
      "setae  %[r]\n\t"
      : [r] "=r" (result), [p] "=m" (*dest) // inputs
      : [x] "r" (x), [y] "r" (y)            // outputs
      : "%rax", "%rdx"                      // modified registers
      );

  return (int) result;
}
