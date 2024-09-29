rfun:
  pushq   %rbx        ; save rbx
  movq    %rdi, %rbx  ; rbx = x
  movl    $0, %eax    ; ret = 0
  testq   %rdi, %rdi
  je      .L2         ; if x == 0: goto .L2
  shrq    $2, %rdi    ; 
  call    rfun        ; rfun(x >> 2)
  addq    %rbx, %rax  ; x + rfun(x >> 2)
.L2
  popq    %rbx       ; restore rbx
  ret
