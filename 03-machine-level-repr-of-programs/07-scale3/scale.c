// rdi: x, rsi: y, rdx: z
// leaq (%rsi, %rsi, 9), %rbx      t = 10 * %rsi = 10 * y
// leaq (%rbx, %rdx), %rbx         t = t + z = 10y + z
// lead (%rbx, %rdi, %rsi), %rbx   t = t + x * y = xy + 10y + z
// ret

short scale3(short x, short y, short z) {
  short t = 10 * y + z + x * y;
  return t;
}
