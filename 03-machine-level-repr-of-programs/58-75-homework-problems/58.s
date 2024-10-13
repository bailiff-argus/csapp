decode2:
  subq     %rdx, %rsi // y -= z
  imulq    %rsi, %rdi // x *= y
  movq     %rsi, %rax // ret = y
  salq     $63,  %rax // ret << 63
  sarq     $63,  %rax // ret >> 63
  xorq     %rdi, %rax // ret ^= x
