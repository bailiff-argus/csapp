// loop_while2:
//   testq   %rsi, %rsi
//   jle     .L8         ; jle b <= 0 OR next b > 0
//   movq    %rsi, %rax  ; result = b
// .L7:
//   imulq   %rdi, %rax  ; result *= a
//   subq    %rdi, %rsi  ; b = b - a
//   testq   %rsi, %rsi
//   jg .L7              ; b > 0 continue
//   rep; ret
// .L8:                  ; b <= 0
//   movq    %rsi, %rax  ; result = b
//   ret

//                  rdi     rsi
long loop_while2(long a, long b) {
  long result = b;
  while (b > 0) {
    result = result * a;
    b = b - a;
  }

  return result;
}
