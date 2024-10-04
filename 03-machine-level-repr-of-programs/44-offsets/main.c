#include <stdio.h>

// alignment recommendations:
// char -- mul of 1,
// short -- mul of 2,
// int -- mul of 4,
// long, pointer -- mul of 8

struct P1 { // alignment 8
  short i;          // 0
  int c;            // 4
  int *j;           // 8
  short *d;         // 16
};                  // total 24

struct P2 { // alignment 8
  int i[2];         // 0
  char c[8];        // 8
  short s[4];       // 16
  long *j;          // 24
};                  // total 32

struct P3 { // alignment 8
  long w[2];        // 0
  int *c[2];        // 16
};                  // total 32

struct P4 { // alignment 8
  char w[16];       // 0
  char *c[2];       // 16
};                  // total 32

struct P5 { // alignment 8
  struct P4 a[2];   // 0
  struct P1 t;      // 64
};                  // total 88

int main(void) {
  printf("P1: %lu\n", sizeof(struct P1));
  printf("P2: %lu\n", sizeof(struct P2));
  printf("P3: %lu\n", sizeof(struct P3));
  printf("P4: %lu\n", sizeof(struct P4));
  printf("P5: %lu\n", sizeof(struct P5));
  return 0;
}
