void umult_full(unsigned long x, unsigned long y, unsigned long *dest) {
  asm(
    "mov      %[x], %%rax\n\t"
    "mulq     %[y]\n\t"
    "mov      %%rax, %[dst_lo]\n\t"
    "mov      %%rdx, %[dst_hi]"
    : [dst_lo] "=m" (dest[0]), [dst_hi] "=m" (dest[1])
    : [x] "r" (x), [y] "r" (y)
    : "%rax", "%rdx"
  );
}

