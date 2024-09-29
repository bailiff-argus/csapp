sum_element:
  leaq   0(,%rdi,8), %rdx     ;; rdx = 8i
  subq   %rdi, %rdx           ;; rdx = 7i
  addq   %rsi, %rdx           ;; rdx = 7i + j
  leaq   (%rsi,%rsi,4), %rax  ;; rax = 5j
  addq   %rax, %rdi           ;; rdi = i + 5j
  movq   Q(,%rdi,8), %rax     ;; rax =  M[Xq + 8(i + 5j)], line len -- 5 (line of Q is M)
  addq   P(,%rdx,8), %rax     ;; rax += M[Xp + 8(7i + j)], line len -- 7 (line of P is N)
