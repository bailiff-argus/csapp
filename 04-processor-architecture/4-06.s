absSum:
  irmovq  $8,     %r8
  irmovq  $1,     %r9
  xorq    %rax,   %rax
  andq    %rsi,   %rsi
  jmp     absSum_test
absSum_loop:
  mrmovq  (%rdi), %r10
  xorq    %r11,   %r11
  subq    %r10,   %r11
  cmovge  %r11,   %r10
absSum_ispos:
  addq    %r10,   %rax
  addq    %r8,    %rdi
  subq    %r9,    %rsi
absSum_test:
  jne     absSum_loop
  ret

