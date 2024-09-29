; long P(long x)
; x in %rdi
P:
  pushq   %r15
  pushq   %r14
  pushq   %r13
  pushq   %r12
  pushq   %rbp
  pushq   %rbx
  subq    $24, %rsp     ; allocate 24 bytes
  movq    %rdi, %rbx    ; %rbx = x     (a0)
  leaq    1(%rdi), %r15 ; %r15 = x + 1 (a1)
  leaq    2(%rdi), %r14 ; %r14 = x + 2 (a2)
  leaq    3(%rdi), %r13 ; %r13 = x + 3 (a3)
  leaq    4(%rdi), %r12 ; %r12 = x + 4 (a4)
  leaq    5(%rdi), %rbp ; %rbp = x + 5 (a5) -- callee-saved registers up to this point
  leaq    6(%rdi), %rax ; %rax = x + 6 (a6)
  movq    %rax, (%rsp)  ; x + 6 (a6) -> STACK
  leaq    7(%rdi), %rdx ; %rdx = x + 7 (a7)
  movq    %rdx, 8(%rsp) ; x + 7 (a7) -> STACK
  movl    $0, %eax      ; %rax = 0
  call Q
  ;  ...

; A: a0-5 get stored in all 6 callee-saved registers
; B: a6-7 get stored on the stack before the call to Q
; C: All of the local values could not be stored in callee-saved registers,
;    because there are more values than there are callee-saved registers
