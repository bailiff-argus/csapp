fix_prod_ele:
  salq    $6, %rdx            ;; rdx = 64i
  addq    %rdx, %rdi          ;; Aptr = Xa + 64i = Xa + 4 * 16 * i = Xa + L * N * i
  leaq    (%rsi,%rcx,4), %rcx ;; Bptr = Xb + k * 4 = Xb + 4 * k = Xb + L * k
  leaq    1024(%rcx), %rsi    ;; Bend = Xb + 1024 + k = Xb + 4 * 16 * 16 + k = Xb + L * N * N + k
  movl    $0, %eax
.L7:
  movl    (%rdi), %edx
  imull   (%rcx), %edx
  addl    %edx, %eax
  addq    $4, %rdi
  addq    $64, %rcx
  cmpq    %rsi, %rcx
  jne     .L7
  rep
  ret
