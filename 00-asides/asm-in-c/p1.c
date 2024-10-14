int tmult_ok(long x, long y, long *dest) {
  unsigned char ret = 0;

  asm(
    "imulq    %[x], %[y]\n\t"
    "mov      %[y], %[dst]\n\t"
    "setae    %[ret]"
    : [dst] "=m" (*dest), [ret] "=r" (ret)
    : [x] "r" (x), [y] "r" (y)
  );

  return (int) ret;
}
