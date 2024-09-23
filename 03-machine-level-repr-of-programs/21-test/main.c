//             rdi      rsi
short test(short x, short y) {
  short val = y + 12;
  if (x < 0) {
    if (x >= y) {
      val = x | y;
    } else {
      val = x * y;
    }
  } else if (y >= 10) {
    val = x / y;
  }
  return val;
}

// test
//   leaq     12(%rsi), %rbx      ; val = y + 12
//   testq    %rdi, %rdi          ; test x
//   jge      .L2                 ; x >= 0 -> jump .L2
//   movq     %rdi, %rbx          ; val = x
//   imulq    %rsi, %rbx          ; val = val * y = x * y
//   movq     %rdi, %rdx          ; temp = x
//   orq      %rsi, %rdx          ; temp = y | temp = x | y
//   cmpq     %rsi, %rdi          ; x - y
//   cmovge   %rdx, %rbx          ; (x-y >= 0) -> val = temp  ->
//   ret                          ; -> (x >= y) ? (x | y) : (x * y)
// .L2:
//   idivq    %rsi, %rdi          ; x = x / y
//   cmpq     $10, %rsi           ; y - 10
//   cmovge   %rdi, %rbx          ; (y-10 >= 0) -> val = x
