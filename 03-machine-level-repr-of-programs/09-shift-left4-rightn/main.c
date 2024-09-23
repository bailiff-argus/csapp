long shift_left4_rightn(long x, long n) {
  x <<= 4;
  x >>= n;
  return x;
}

// shift_left4_rightn(long x, long n)
// x: %rdi; n: %rsi
// shift_left4_rightn:
//   movq    %rdi, %rax
//   sal     $4,   %rax
//   movl    %esi, %ecx
//   ssar    %cl,  %rax
//   ret
