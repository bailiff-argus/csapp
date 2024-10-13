store_prod:
  movq   %rdx, %rax    ;; rax = y
  cqto                 ;; y -> [rdx(hi), rax(lo)], rdx is -1 if y is negative, 0 if not
  movq   %rsi, %rcx    ;; x -> rcx
  sarq   $63,  %rcx    ;; rcx is -1 if x is negative, 0 if not
  imulq  %rax, %rcx    ;; rcx = -(x_63 * y_lo)
  imulq  %rsi, %rdx    ;; rdx = -(x_lo * y_63)
  addq   %rdx, %rcx    ;; rcx = -(x_63 * y_lo + y_63 * x_lo)
  mulq   %rsi          ;; rdx, rax = ux * uy
  addq   %rcx, %rdx    ;; rdx -= (x_63 * y_lo + y_63 * x_lo)
  movq   %rax, (%rdi)  ;; store p_lo
  movq   %rdx, 8(%rdi) ;; store p_hi

;; if anything is ever 2^128 or up, we can remove it since it overflows
;; ux = x + x_63 * 2^64
;; uy = y + y_63 * 2^64
;; ux * uy = x * y + x * y_63 * 2^64 + y * x_63 * 2^64 + (x_63 * y_63 * 2^128) !overflow!
;; ux * uy = x * y + (x * y_63 + y * x_63) * 2^64
;; x * y = ux * uy - (x * y_63 + y * x_63) * 2^64
;; p_lo = (ux * uy)mod2^64
;; p_hi = (ux * uy)/2^64 - (x * y_63 + y * x_63) = (ux * uy)/2^64 + x * y_lo + y * x_lo
