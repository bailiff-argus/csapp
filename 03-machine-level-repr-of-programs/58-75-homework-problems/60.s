loop:
  movl     %esi, %ecx   // ecx = (int)n
  movl     $1,   %edx   // mask = 1
  movl     $0,   %eax   // result = 0
  jmp      .L2
.L3:
  movq     %rdi, %r8    // r8 = x
  andq     %rdx, %r8    // r8 = x & mask
  orq      %r8,  %rax   // result |= (x & rdx)
  salq     %cl,  %rdx   // mask << n
.L2:
  testq    %rdx, %rdx   // while mask != 0
  jne      .L3
  rep ret

;; A.
;;   %rdi holds x
;;   %rsi originally, then %rcx/%ecx/%cl holds n
;;   %rax holds result
;;   %rdx holds mask

;; B.
;;   Initial value for result is 0, and 1 for mask.

;; C.
;;   Mask is not zero.

;; D.
;;   Mask is shifted left by n.

;; E.
;;   Result is updated to contain every nth bit of x, starting from the first bit.
