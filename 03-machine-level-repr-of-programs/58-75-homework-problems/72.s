aframe:
  pushq   %rbp
  movq    %rsp,        %rbp # save the stack pointer
  subq    $16,         %rsp # allocate 16 bytes (i)
  leaq    30(,%rdi,8), %rax # rax = 30 + n * sizeof(long)
  andq    $-16,        %rax # round down to nearest 16
  subq    %rax,        %rsp # allocate rax bytes for p
  leaq    15(%rsp),    %r8
  andq    $-16,        %r8  # p is %rsp rounded up to the nearest 16
  # ...

# A. For an odd n, the effect is to round up to align to 16 and add extra 16 bytes
#    For an even n, the alignment is already there. Just add extra 16 bytes
#    8(2k) + 30 = 16k + 16 + 14 => 8(2k) + 16
#    8(2k+1) + 30 = 16k + 8 + (8 + 16 + 6) => 16k + 16 + 16 = 8(2k + 1) + 24

#    s2 = s1 - ((8n + 30) & ~0xF)
#    Even n: s2 = s1 - (8n + 16)
#    Odd n:  s2 = s1 - (8n + 24)

#    The added 16 or 24 make up the sum of e1 and e2.

# B. p is %rsp rounded up to the nearest 16. Thus, e2=(s2-p) is anywhere between 0 and 15.
#    p = (s2 + 15) & ~0xF

# C. Maximum: with odd n, e1 + e2 = 24. If e2 = 0, e1 = 24. That means that s2=p and s1 is 8-aligned.
#    Minimum: with even n, e1 + e2 = 16. If e2 = 15, e1 = 1. That means that s1 must be 1 byte behind 16-alignment.

# D. p is strictly 16-aligned, s2 has the same alignment relative to 16 as s1.
