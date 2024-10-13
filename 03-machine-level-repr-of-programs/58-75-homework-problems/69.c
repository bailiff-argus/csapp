// (288 - 8) / 40 = 7
#define CNT 7

typedef struct {
  long idx;
  long x[4];
} a_struct;

typedef struct {
  int first;       // offset 0
  a_struct a[CNT]; // offset 8
  int last;        // offset 288
} b_struct;

void test(long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}
