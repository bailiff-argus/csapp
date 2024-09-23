// C goto negative
//     t = expr
//     if (!t) goto false;
//     do-if-true
//     goto quit
// false:
//     do-if-false
// quit:
//     finally-do

// C goto positive
//     t = expr
//     if (t) goto true;
//     do-if-false
//     goto quit
// true:
//     do-if-true
// quit:
//     finally-do

long lt_cnt = 0, ge_cnt = 0;

long gotodiff_se_neg(long x, long y) {
  long result;
  if (x >= y)
    goto x_ge_y;
  lt_cnt++;
  result = y - x;
  return result;
x_ge_y:
  ge_cnt++;
  result = x - y;
  return result;
}

long gotodiff_se_pos(long x, long y) {
  long result;
  if (x < y)
    goto x_lt_y;
  ge_cnt++;
  result = x - y;
  return result;
x_lt_y:
  lt_cnt++;
  result = y - x;
  return result;
}
