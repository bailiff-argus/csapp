.L8: // MODE_E
  movl      $27, %eax
  ret
.L3: // MODE_A
  movq      (%rsi), %rax
  movq      (%rdi), %rdx
  movq      %rdx,   (%rsi)
  ret
.L5: // MODE_B
  movq      (%rdi), %rax
  addq      (%rsi), %rax
  movq      %rax,   (%rdi)
  ret
.L6: // MODE_C
  movq      $59,    (%rdi)
  movq      (%rsi), %rax
  ret
.L7: // MODE_D
  movq      (%rsi), %rax
  movq      %rax,   (%rdi)
  movl      $27,    %eax
  ret
.L9: // default
  movl      $12,    %eax
  ret
