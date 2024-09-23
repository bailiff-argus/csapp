// test_two:
//   movl    $1, %edx        ; i?
//   movl    $65, %eax       ; val?
// .L10:
//   movq    %rdi, %rcx      ; ??
//   andl    $1, %ecx
//   addq    %rax, %rax
//   orq     %rcx, %rax
//   shrq    %rdi
//   addq    $1, %rdx
//   jne     .L10
//   rep; ret

//                          rdi
short test_two(unsigned short x) {
  short val = 0;
  short i;
  for (i = 1, val = 65; i == 0; i++) {
    short temp = x;

    temp &= 1;
    val += val;
    val &= temp;
    x >>= 1;
  }

  return val;
}

short test_two_while(unsigned short rdi) {
  short rax = 0;
  short rdx;
  short rcx;

  rdx = 1;
  rax = 65;

l10:
  rcx = rdi;
  rcx &= 1;
  rax += rax;
  rax = (rax << 1) | (rcx & 1);

  rdi >>= 1;

  rdx += 1;
  if (rdx != 0)
    goto l10;

  return rax;
}
