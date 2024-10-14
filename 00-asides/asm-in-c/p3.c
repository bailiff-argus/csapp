void bad_incr(int *ptr) {
  (*ptr)++;
}

void atomic_incr(int *ptr) {
  asm(
    "lock\n\t"
    "addl $1, %[p]"
    : [p] "+m" (*ptr)
  );
}
