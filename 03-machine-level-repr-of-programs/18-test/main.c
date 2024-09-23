// asm:
// test:
//   leaq     (%rdx,%rsi), %rax ; val = z + y
//   subq     %rdi, %rax        ; val = val - x
//   cmpq     $5, %rdx          ; z - 5
//   jle      .L2               ; (z - 5) <= 0 -> goto L2
//   cmpq     $2, %rsi          ; y - 2
//   jle      .L3               ; (y - 2) <= 0 -> goto L3
//   movq     %rdi, %rax        ; val = x
//   idivq    %rdx, %rax        ; val = val / z
//   ret
// .L3: ; (z > 5) && (y <= 2)
//   movq     %rdi, %rax        ; val = x
//   idivq    %rsi, %rax        ; val = val / y
//   ret
// .L2 ; (z <= 5)
//   cmpq     $3, %rdx          ; z - 3
//   jge      .L4               ; (z - 3) >= 0 -> goto L4
//   movq     %rdx, %rax        ; val = z
//   idivq    %rsi, %rax        ; val = val / y
// .L4
//   rep; ret

//            %rdi,    %rsi,    %rdx
short test(short x, short y, short z) {
  short val = (z + y) - x;
  if (z > 5) {
    if (y > 2) {
      val = x / z;
    } else {
      val = x / y;
    }
  } else if (z < 3) {
    val = z / y;
  }
  return val;
}
