```asm
0...0400540 <last>:
   400540:  48 89 f8           mov     %rdi, %rax       ; L1: u
   400543:  48 0f af c6        imul    %rsi, %rax       ; L2: u * v
   400547:  c3                 retq                     ; L3: return

0...0400548 <first>:
   400548:  48 8d 77 01        lea     0x1(%rdi),%rsi   ; F1: x + 1
   40054c:  48 83 ef 01        sub     $0x1,%rdi        ; F2: x - 1
   400550:  e8 eb ff ff ff     callq   400540 <last>    ; F3: Call last(x-1, x+1)
   400555:  f3 c3              repz retq                ; F4: Return
   .
   .
   .
   400560:  e8 e3 ff ff ff     callq   400548 <first>   ; M1: Call first(10)
   400565:  48 89 c2           mov     %rax,%rdx        ; M2: Resume
```

M1: PC=0x400560 INSTR=callq    %rdi=10              %rsi=-            %rax=-             %rsp=0x7fffffffe820    *%rsp=--------  Desc="call first(10)"
F1: PC=0x400548 INSTR=lea      %rdi=10              %rsi=-            %rax=-             %rsp=0x7fffffffe818    *%rsp=0x400565  Desc="store %rdi+1 -> %rsi"
F2: PC=0x40054c INSTR=sub      %rdi=10              %rsi=11           %rax=-             %rsp=0x7fffffffe818    *%rsp=0x400565  Desc="store %rdi-1 -> %rdi"
F3: PC=0x400550 INSTR=callq    %rdi=9               %rsi=11           %rax=-             %rsp=0x7fffffffe818    *%rsp=0x400565  Desc="call last(9, 11)"

L1: PC=0x400540 INSTR=mov      %rdi=9               %rsi=11           %rax=-             %rsp=0x7fffffffe810    *%rsp=0x400555  Desc="store %rdi->%rax"
L2: PC=0x400543 INSTR=imul     %rdi=9               %rsi=11           %rax=9             %rsp=0x7fffffffe810    *%rsp=0x400555  Desc="store %rax * %rsi -> %rax"
L3: PC=0x400547 INSTR=retq     %rdi=9               %rsi=11           %rax=99            %rsp=0x7fffffffe810    *%rsp=0x400555  Desc="return 99 from last()"

F4: PC=0x400555 INSTR=retq     %rdi=9               %rsi=11           %rax=99            %rsp=0x7fffffffe818    *%rsp=0x400565  Desc="return 99 from first()"

M2: PC=0x400565 INSTR=mov      %rdi=9               %rsi=11           %rax=99            %rsp=0x7fffffffe820    *%rsp=--------  Desc="store %rax -> %rdx"
