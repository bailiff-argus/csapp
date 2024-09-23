// rdi, rsi, rdx, rcx
void remdiv(long x, long y, long *qp, long *rp) {
  long q = x / y;
  long r = x % y;
  *qp = q;
  *rp = r;
}

// remdiv:
//   mov    %rdi,%rax
//   mov    %rdx,%r8
//   cqto
//   idiv   %rsi
//   mov    %rax,(%r8)
//   mov    %rdx,(%rcx)
//   ret

void uremdiv(unsigned long x, unsigned long y, unsigned long *qp,
             unsigned long *rp) {
  unsigned long q = x / y;
  unsigned long r = x % y;
  *qp = q;
  *rp = r;
}

// uremdiv:
//   mov    %rdi,%rax
//   mov    %rdx,%r8
//   mov    $0,%eax
//   div    %rsi
//   mov    %rax,(%r8)
//   mov    %rdx,(%rcx)
//   ret
