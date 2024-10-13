;; long cread(long *xp) {
;;   return (xp ? *xp : 0);
;; }

cread:
  mov     $0,     %rax
  testq   %rdi,   %rdi
  cmovnz  (%rdi), %rax
  ret
