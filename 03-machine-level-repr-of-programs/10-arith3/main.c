// long arith3(long x, long y, long z)
//                 %rdi,    %rsi,    %rdx
//
// arith3:
//  orq   %rsi, %rdx
//  sarq  $9,   %rdx
//  notq  %rdx
//  movq  %rdx, %bax
//  subq  %rsi, %rbx
//  ret

long arith3(long x, long y, long z) {
  long p1 = y | z;
  long p2 = p1 >> 9;
  long p3 = ~p2;
  long p4 = p3 - y;
  return p4;
}
