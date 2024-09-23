//                rdi
short dw_loop(short x) {
  short y = x / 9;
  short *p = &x;
  short n = 4 * x;
  do {
    x += y;
    (*p) += 5;
    n -= 2;
  } while (n > 0);
  return x;
}

// dw_loop:
//   movq    %rdi, %rbx          ; rbx = x
//   movq    %rdi, %rcx          ; y = x
//   idivq   $9, %rcx            ; y = y / 9
//   leaq    (,%rdi,4), %rdx     ; n = x * 4
// .L2
//   leaq    5(%rbx,%rcx), %rcx  ; y = x + y + 5
//   subq    $1, %rdx            ; n = n - 1
//   testq   %rdx, %rdx          ; n?
//   jg      .L2                 ; n > 0 -> .L2
//   rep; ret
