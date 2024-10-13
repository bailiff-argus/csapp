.L6:
  movq    (%rdx), %rcx
  movq    (%rax), %rsi
  movq    %rsi,   (%rdx)
  movq    %rcx,   (%rax)
  addq    $8,     %rdx   ;; moves along rows,  rdx is A[i][j]
  addq    $120,   %rax   ;; moves across rows, rax is A[j][i]
  cmpq    %rdi,   %rax
  jne     .L6
  
;; 120 = M * sizeof(long) -> M = 120 / 8 = 15
