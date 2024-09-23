#include <stdio.h>

// test_one:
//   movl    $1, %eax    ; result = 1
//   jmp .L5             ; jump to middle
// .L6:
//   xorq    %rdi, %rax
//   shrq    %rdi
// .L5:
//   testq   %rdi, %rdi
//   jne     .L6
//   andl    $0, %eax
//   ret

//                          rdi
short test_one(unsigned short x) {
  short result = 1;
  while (x != 0) {
    result = result ^ x;
    x = x >> 1;
  }
  return result & 1;
}

int main(void) {
  for (int i = 0; i < 10; i++) {
    printf("%d parity: %d\n", i, test_one(i));
  }

  return 0;
}
