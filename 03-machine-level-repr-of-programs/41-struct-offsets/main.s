;; st in %rdi
st_init:
  movl   8(%rdi), %eax   // eax = st->s.x
  movl   %eax, 10(%rdi)  // st->s.y = eax (= st->s.x)
  leaq   10(%rdi), %rax  // rax = &(st->s.y)
  movq   %rax, (%rdi)    // st->p = rax (= &(st->s.y))
  movq   %rdi, 12(%rdi)  // st->next = st
  ret
