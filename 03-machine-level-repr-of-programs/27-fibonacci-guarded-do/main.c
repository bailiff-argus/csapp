#include <stdio.h>

long fibonacci_orig(int x) {
  int i = 2;
  int next = x, first = 0, second = 1;

  if (x <= 1)
    goto done;

do_loop:
  next = first + second;
  first = second;
  second = next;
  i++;
  if (i <= x)
    goto do_loop;

done:
  return next;
}

int main(void) {
  for (int i = 0; i < 10; i++) {
    printf("%d: %ld\n", i, fibonacci_orig(i));
  }
}
