#include <string.h>
#include <sys/types.h>

// No conditionals, loops, switches or macros
// No division, modulus, or multiplication
// No relative comparison (<, >, >=, <=)
//
// Yes all logic and bit-level
// Yes left and right shifts by up to w-1
// Yes add and subtract
// Yes INT_MIN and INT_MAX
// Yes int<->uint cast

void copy_int(int val, void *buf, int maxbytes) {
  size_t x;
  if (maxbytes - (int)sizeof(val) >= 0) {
    memcpy(buf, (void *)&val, sizeof(val));
  }
}
