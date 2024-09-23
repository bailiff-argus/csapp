#define OP /
//              rdi
short arith(short x) {
  // hi
  return x OP 16;
}

// arith:
//   leaq   15(%rdi), %rbx  ; rbx = x + 15 -- biasing for negative division
//   testq  %rdi, %rdi      ; x & x
//   cmovns %rdi, %rbx      ; x >= 0 -> rbx = x
//   sarq   $4, %rbx        ; rbx >> 4 (rbx / 16)
//   ret
