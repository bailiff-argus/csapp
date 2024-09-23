#include <limits.h>
#include <string.h>
#include <sys/types.h>

// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes != ==
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast

// addition that saturates to TMin or TMax
int saturating_add(int x, int y) {
  int res, pos_of, neg_of;

  res = x + y;
  pos_of = !(x & INT_MIN) && !(y & INT_MIN) && (res & INT_MIN);
  neg_of = (x & INT_MIN) && (y & INT_MIN) && !(res & INT_MIN);
  (pos_of && (res = INT_MAX)) || (neg_of && (res = INT_MIN));

  return res;
}
