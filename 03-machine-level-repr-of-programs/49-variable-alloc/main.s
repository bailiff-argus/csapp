vframe:
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  leaq    22(,%rdi,8), %rax     ;A; rax = 22 + rdi * 8 = 22 + 8n
  andq    $-16, %rax            ;A; rax & -16 = rax & -(0x10000) = rax & 0x1111,1111,1111,0000
  subq    %rax, %rsp            ;A; rsp -= rax
  leaq    7(%rsp), %rax         ;B; rax = rsp + 7
  shrq    $3, %rax              ;B; rax = rax / 8
  leaq    0(,%rax,8), %r8       ;B; r8  = rax * 8
  movq    %r8, %rcx
.L3:
  movq    %rdx, (%rcx,%rax,8)
  addq    $1, %rax
  movq    %rax, -8(%rbp)
.L2:
  movq    -8(%rbp), %rax
  cmpq    %rdi, %rax
  jl      .L3
  leave
  ret


; A. 5-7:  Allocate [(8n + 22) rounded down to the nearest 16] bytes on the stack. s2 is (s1 - that value).
; n = 2k     => 8(2k) + 22     = 8(2k) + 22 = 16k + (16 + 6)  => 16k + 16 = 8(2k) + 16     = 8n + 16
; n = 2k + 1 => 8(2k + 1) + 22 = 8(2k) + 30 = 16k + (16 + 14) => 16k + 16 = 8(2k + 1) + 8  = 8n + 8

; B. 8-10: rax is rsp rounded up to the nearest 8. That value is p.

; C.  n          s1          s2          p          e1          e2
;     5        2,065       2,017      2,024          1           7
;     6        2,064       2,000      2,008         16           0
; 
; n=5: s2 = s1 - (8n + 22 down to nearest 16) = 2,065 - (62 down) = 2,065 - 48 = 2,017
;      p  = (s2 + 7) / 8 * 8 = 2,024
;      e1 = s1 - (p + 8n) = 2,065 - 2,064 = 1
;      e2 = p - s2 = 7
;
; n=6: s2 = 2,064 - 64 = 2,000
;      p  = (2,000 + 7) / 8 * 8 = 2,000
;      e1 = 2,064 - 2,048 = 16
;      e2 = 2,000 - 2,000 = 0
;
; D. s2 preserves the offset s1 has against nearest multiple of 16.
;    p is guaranteed to be 8-aligned.
