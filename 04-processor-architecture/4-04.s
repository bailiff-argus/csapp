//                     %rdi        %rsi
// long rproduct(long *start, long count) {
//   if (count <= 1)
//     return 1;
//   return *start * rproduct(start + 1, count - 1);
// }

rproduct:
  irmovq    $1,  %rax
  irmovq    $1,  %r9
  irmovq    $8,  %r10
  subq      %r9, %rsi
  jle       exit
mult:
  pushq     %rbx
  mrmovq    (%rdi), %rbx
  addq      %r10,   %rdi
  call      rproduct
  mulq      %rbx, %rax
  popq      %rbx
exit:
  ret
