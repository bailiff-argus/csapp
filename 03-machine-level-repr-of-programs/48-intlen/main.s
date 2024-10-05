intlen_nofstack:
  subq    $40, %rsp      ; allocate 40 bytes on stack
  movq    %rdi, 24(%rsp) ; put x on %rsp+24
  leaq    24(%rsp),%rsi  ; address of x = %rsp + 24 (offset 24 from stack top)
  movq    %rsp, %rdi     ; address of buf = %rsp    (offset 0 from stack top)
  call    iptoa

intlen_fstack:
  subq    $56, %rsp       ; allocate 56 bytes on stack
  movq    %fs:40, %rax    ; load canary value into rax
  movq    %rax, 40(%rsp)  ; put canary at offset 40
  xorl    %eax, %eax
  movq    %rdi, 8(%rsp)   ; put x at offset 8
  leaq    8(%rsp),%rsi    ; pointer to x
  movq    16(%rsp), %rdi  ; put buf at offset 16
  call    iptoa

; A. In nofstack, buf is at offset 0, and v is at offset 24.
;    In fstack, v is at offset 8, buf is at offset 16, canary is at offset 40.

; B. In the rearranged order, overflowing buf can only allow an attacker to overwrite the canary,
;    but v would be unaffected.
