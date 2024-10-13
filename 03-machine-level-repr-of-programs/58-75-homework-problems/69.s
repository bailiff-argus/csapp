test:
  mov       0x120(%rsi),   %ecx                # ecx = bp + 0x120 (last)
  add       (%rsi),        %ecx                # ecx += bp        (first)
  lea       (%rdi,%rdi,4), %rax                # rax = 5i
  lea       (%rsi,%rax,8), %rax                # rax = bp + 40i
  mov       0x8(%rax),     %rdx                # rdx = *(rax + 8) -- this is the index
  movslq    %ecx,          %rcx                # rcx = bp->first + bp->last
  mov       %rcx,          0x10(%rax,%rdx,8)   # bp + 40i + 16 + idx * 8
  retq
