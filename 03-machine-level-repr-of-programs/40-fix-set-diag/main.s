fix_set_diag:
  movl    $0, %eax
.L13:
  movl    %esi, (%rdi,%rax)
  addq    $68, %rax
  cmpq    $1088, %rax
  jne     .L13
  rep
  ret
