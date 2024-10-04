#include <stdio.h>

struct { // al 8
  int    *a; // 0
  float   b; // 8
  char    c; // 12
  short   d; // 14 (+1)
  long    e; // 16
  double  f; // 24
  int     g; // 32
  char   *h; // 40 (+4)
} rec;       // 48 (no padding needed)

struct {
  int    *a; // 0
  long    e; // 8
  double  f; // 16
  char   *h; // 24
  float   b; // 32
  int     g; // 36
  short   d; // 40
  char    c; // 42
} opt_rec;   // 43 -+5-> 48 (padded)

int main(void) {
  printf("%lu vs %lu\n", sizeof(rec), sizeof(opt_rec));
  return 0;
}
