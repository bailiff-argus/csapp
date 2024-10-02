test:
  movl     $1, %eax         // ret = 1;
  jmp      .L2              // goto .L2;

.L3:
  imulq    (%rdi), %rax     // ret = ret * ptr->v;
  movq     2(%rdi), %rdi    // ptr = ptr->p;

.L2:
  testq    %rdi, %rdi       // test
  jne      .L3              // if (ptr != 0) goto .L3;
  rep ret
