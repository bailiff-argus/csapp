// iaddq V, rB

sum:
  xorq   %rax,   %rax
  andq   %rsi,   %rsi
  jmp    test
loop:
  mrmovq (%rdi), %r10
  addq   %r10,   %rax
  iaddq  $0x8,   %rdi
  iaddq  $-0x1,  %rsi
test:
  jne    loop
  ret
