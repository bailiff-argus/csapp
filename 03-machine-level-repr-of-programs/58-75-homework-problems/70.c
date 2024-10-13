union ele {
  struct {
    long *p;         // offset 0
    long y;          // offset 8
  } e1;
  struct {
    long x;          // offset 0
    union ele *next; // offset 8
  } e2;
}; // 16 bytes total

void proc (union ele *up) {
  up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
}
