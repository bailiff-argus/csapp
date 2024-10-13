#include <stdint.h>
#include <assert.h>
#include <stdio.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range_asm(float x) {
  const float zero = 0;
  range_t ret = 0;

  asm("mov      $1,    %%edi\n\t"
      "mov      $2,    %%esi\n\t"
      "mov      $3,    %%edx\n\t"
      "vucomiss %[x],  %[z]\n\t"
      "cmovz    %%edi, %[r]\n\t"
      "cmovb    %%esi, %[r]\n\t"
      "cmovp    %%edx, %[r]\n\t"
      : [r] "=r" (ret)                // outputs
      : [x] "x" (x), [z] "x" (zero)   // inputs
      : "%edi", "%esi", "%edx"        // overwrites
  );

  return ret;
}

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
