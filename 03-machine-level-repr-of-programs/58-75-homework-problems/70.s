proc:
  movq  8(%rdi), %rax    # rax = up.e1.y / up.e2.next
  movq  (%rax),  %rdx    # deref -> ^ rax = up.e2.next
  movq  (%rdx),  %rdx    # *next.e1.p
  subq  8(%rax), %rdx    # next.e1.p - y
  movq  %rdx,    (%rdi)  # up.e2.x = ^
  ret
