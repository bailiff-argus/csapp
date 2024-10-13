store_ele:
  leaq     (%rsi,%rsi,2), %rax  ;; rax = 3j
  leaq     (%rsi,%rax,4), %rax  ;; rax = j + 4(3j) = 13j
  movq     %rdi, %rsi           ;; rsi = i
  salq     $6,   %rsi           ;; rsi = i * 2^6 = 64i
  addq     %rsi, %rdi           ;; rdi = 65i
  addq     %rax, %rdi           ;; rdi = 65i + 13j
  addq     %rdi, %rdx           ;; k = 65i + 13j + k
  movq     A(,%rdx,8), %rax     ;; rax = A + (65i + 13j + k) * sizeof(long)
  movq     %rax, (%rcx)         ;; dest = rax
  movl     $3640,%eax           ;; R * S * T * sizeof(long) = 3640 => R*S*T = 455 = 5 * 7 * 13
  ret
