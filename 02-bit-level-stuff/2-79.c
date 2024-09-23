#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

int mul3div4(int x) {
  return ((x << 2) - x) >> 2;
}
