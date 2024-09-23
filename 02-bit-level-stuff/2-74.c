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

int tsub_ok(int x, int y) {
  if (y == INT_MIN) {
    return 0;
  } else if (y < 0) {
    return x + (-y) > x;
  } else { // (y >= 0)
    return x - y <= x;
  }
}
