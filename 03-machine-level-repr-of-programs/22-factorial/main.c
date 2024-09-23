#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define int_t int32_t
#define PRint PRId32

int_t fact_do(int_t n) {
  int_t res = 1;
  volatile int_t prev;
  do {
    prev = res;
    res *= n;
    if (res / prev != n)
      printf("Overflow! %" PRint " * %" PRint " = %" PRint "\n", prev, n, res);
    n = n - 1;
  } while (n > 1);
  return res;
}

int_t fact_do_goto(int_t n) {
  int_t res = 1;
do_label:
  res *= n;
  n = n - 1;
  if (n > 1)
    goto do_label;
  return res;
}

// fact_do:
//   movl       $1, %eax
// .L2:
//   imulq    %rdi, %rdx
//   subq       $1, %rdi
//   cmpq       $1, %rdi
//   jg       .L2
//   ret

int main(void) {
  int_t res = fact_do(14);
  printf("Hi %" PRint " did not overflow?", res);
  return 0;
}
