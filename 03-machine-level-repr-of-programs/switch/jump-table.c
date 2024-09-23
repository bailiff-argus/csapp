void switch_eg(long x, long n, long *dest) {
  long val = x;

  switch (n) {
  case 100:
    val *= 13;
    break;

  case 102:
    val += 10;
    /*Fall through*/

  case 103:
    val += 11;
    break;

  case 104:
  case 106:
    val *= val;
    break;

  default:
    val = 0;
    break;
  }

  *dest = val;
}

//                     rdi     rsi     rdx
void switch_eg_impl(long x, long n, long *dest) {
  /* Table of code pointers. && is a gcc extension to point at code */
  static void *jt[7] = {&&loc_A, &&loc_def, &&loc_B, &&loc_C,
                        &&loc_D, &&loc_def, &&loc_D};

  unsigned long index = n - 100;
  long val;

  if (index > 6)
    goto loc_def;

  goto *jt[index];

loc_A:
  val = x * 13;
  goto done;

loc_B:
  x = x + 10;

loc_C:
  val = x + 11;
  goto done;

loc_D:
  val = x * x;
  goto done;

loc_def:
  val = 0;
done:
  *dest = val;
}
