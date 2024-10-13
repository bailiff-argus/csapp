sum_col:
  leaq     1(,%rdi,4),    %r8   ;; r8 = n * 4 + 1
  leaq     (%rdi,%rdi,2), %rax  ;; rax = 3 * n
  movq     %rax, %rdi           ;; rdi = 3n
  testq    %rax, %rax           ;; 
  jle      .L4                  ;; if (3n <= 0) goto L4
  salq     $3,   %r8            ;; r8 = 8(4n + 1)
  leaq     (%rsi,%rdx,8), %rcx  ;; rcx = A + 8j
  movl     $0,   %eax           ;; result = 0
  movl     $0,   %edx           ;; i = 0
.L3:
  addq     (%rcx), %rax         ;; result += *(A + 8j + ...i)
  addq     $1,   %rdx           ;; i += 1
  addq     %r8,  %rcx           ;; rcx += 8(4n + 1)
  cmpq     %rdi, %rdx
  jne      .L3                  ;; if (i != 3n) goto .L3
  rep
  ret                           ;; return result
.L4:
  movl     $0, %eax             ;;
  ret                           ;; return 0
