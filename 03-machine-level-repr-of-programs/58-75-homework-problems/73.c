#include <stdint.h>
#include <assert.h>
#include <stdio.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

extern range_t find_range_asm(float x);

//                   %xmm0
range_t find_range(float x) {
  int result;

  if (x < 0)
    result = NEG;
  else if (x == 0)
    result = ZERO;
  else if (x > 0)
    result = POS;
  else
    result = OTHER;
  
  return result;
}

typedef union {
  uint32_t fb;
  float f;
} float_bits;

int main(void) {
  float_bits fb = {0};
  range_t r1, r2;

  for (uint64_t i = 1; i <= UINT32_MAX; i++) {
    fb.fb = (uint32_t) i;
    r1 = find_range(fb.f);
    r2 = find_range_asm(fb.f);
    if (r1 != r2) {
      printf("fb: %u, f: %e, c: %d, asm: %d\n", fb.fb, fb.f, r1, r2);
      return 1;
    }
  }

  return 0;
}
