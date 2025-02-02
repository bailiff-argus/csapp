#include <stdint.h>
#include <stdio.h>

int64_t pop_rsp(void) {
  int64_t res;

  asm(
    "movq   %%rsp,  %%rdi\n\t"
    "pushq  $0xABCD\n\t"
    "popq   %%rsp\n\t"
    "movq   %%rsp, %[res]\n\t"
    "movq   %%rdi, %%rsp\n\t"
    : [res] "=r" (res)
    :
    : "%rdi", "%rax"
  );

  return res;
}

int main(void) {
  printf("0x%lX\n", pop_rsp()); // the result is 0xABCD
  // this means that first the stack pointer is incremented,
  // and then the data is read
  return 0;
}
