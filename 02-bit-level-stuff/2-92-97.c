#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t float_bits;

typedef float_bits (*float_bit_func)(float_bits);
typedef float (*float_func)(float);
typedef int (*float_test)(float_bits);

#define FRAC_BITS 23
#define EXP_BITS 8
#define SIGN_BITS 1

#define EXP_MASK ((float_bits)0xFF << FRAC_BITS)
#define FRAC_MASK (~(float_bits)0x00 >> (EXP_BITS + SIGN_BITS))
#define SIGN_MASK ((float_bits)0x01 << (EXP_BITS + FRAC_BITS))

#define BIAS (127)

static float u2f(float_bits fb) {
  return *((float *)&fb);
}

static float_bits f2u(float f) {
  return *((float_bits *)&f);
}

static int is_special(float_bits f) {
  return (f & EXP_MASK) == EXP_MASK;
}

static int is_nan(float_bits f) {
  return is_special(f) && (f & FRAC_MASK);
}

static int test_base(float_bits fb, float_bit_func fb_func, float_func f_func) {
  float f = u2f(fb);

  float_bits f_res = f2u(f_func(f)), fb_res = fb_func(fb);

  if (f_res == fb_res)
    return 1;

  if (is_nan(f_res) && is_nan(fb_res))
    return 1;

  printf("    | %8s | %8s | %s | %s\n", "val", "res", "float", "fl_res");
  printf("f:  | %.8X | %.8X | %f | %f\n", f2u(f), f_res, f, u2f(f_res));
  printf("fb: | %.8X | %.8X | %f | %f\n", fb, fb_res, u2f(fb), u2f(fb_res));

  return 0;
}

// 2.92 Compute -f. If f in Nan, then return f
float_bits float_negate(float_bits f) {
  if (is_nan(f))
    return f;

  return f ^ SIGN_MASK;
}

static float true_float_negate(float f) {
  return -f;
}

int test_negate(float_bits fb) {
  return test_base(fb, float_negate, true_float_negate);
}

// 2.93 Compute |f|. If f is NaN, then return f
float_bits float_absval(float_bits fb) {
  if (is_nan(fb))
    return fb;

  return fb & ~SIGN_MASK;
}

static float true_float_absval(float f) {
  return fabs(f);
}

int test_absval(float_bits fb) {
  return test_base(fb, float_absval, true_float_absval);
}

// 2.94 Compute 2*f. If f is Nan, then return f
float_bits float_twice(float_bits fb) {
  float_bits normalized;

  // NaN or +-inf
  if (is_special(fb))
    return fb;

  // denormalized
  if ((fb & EXP_MASK) == 0) {
    return (fb << 1) | (fb & SIGN_MASK);
  }

  normalized = fb + (1 << FRAC_BITS);
  if (is_special(normalized))
    return normalized & ~FRAC_MASK;

  return normalized; // first bit of the exponent
}

float true_float_twice(float f) {
  return 2 * f;
}

int test_twice(float_bits fb) {
  return test_base(fb, float_twice, true_float_twice);
}

// 2.95 Compute 0.5 * f. If f is NaN, then return f.
// Round to even!
float_bits float_half(float_bits fb) {
  float_bits sign, exp, frac, result;

  // +-inf, NaN
  if (is_special(fb))
    return fb;

  sign = fb & SIGN_MASK;
  exp = (fb & EXP_MASK) >> (FRAC_BITS);
  frac = fb & FRAC_MASK;

  // denormalized or the smallest power normalized can be shifted right once
  if ((exp == 0) || (exp == 1)) {
    result = sign | ((fb & (EXP_MASK | FRAC_MASK)) >> 1);

    // round to even
    if ((fb & 0x01) && (result & 0x01))
      result += 0x01;

    return result;
  }

  // the rest of normalized must have exp decremented
  return sign | ((exp - 1) << FRAC_BITS) | frac;
}

float true_float_half(float f) {
  return 0.5 * f;
}

int test_half(float_bits fb) {
  return test_base(fb, float_half, true_float_half);
}

// 2.96 Compute (int) fb.
// If conversion causes an overflow or f is NaN, return 0x80000000
// Round towards zero.
int32_t float_f2i(float_bits fb) {
  // float value V = -1^sign * 2^(exp-bias) * (1 + .frac)

  int32_t sign = (fb & SIGN_MASK);
  int32_t exp = (fb & EXP_MASK) >> FRAC_BITS;
  int32_t frac = (fb & FRAC_MASK);
  int32_t bias = (1 << (EXP_BITS - 1)) - 1;

  int32_t E = exp - bias;        // this is just a normal float exponent formula
  uint32_t M = (1 << 23) | frac; // significand is 1.[frac] for normalized
  uint32_t pos_val = 0;

  uint32_t mask = ~0;

  // make sure it's not +-inf or NaN
  if (is_special(fb))
    return 0x80000000;

  // |fb| < 1 -> 0; |fb| == 1 <=> E=0 && M=0
  if (E < 0)
    return 0;

  // M >= 1; << 32 is guaranteed to overflow, so E >= 32 is overflow
  // additionally, << 31 puts a bit onto the sign position, which also indicates
  // overflow
  if (E >= 31)
    return 0x80000000;

  // we must capture (E + 1) *leftmost* bits of the fraction part, extended
  // beyond n=23 to the right with zeroes
  M <<= EXP_BITS;
  mask <<= (31 - E);
  pos_val = (M & mask) >> (31 - E);

  if (!sign)
    return pos_val;

  return -pos_val;
}

int32_t true_float_f2i(float f) {
  return (int32_t)f;
}

int test_f2i(float_bits fb) {
  float f = u2f(fb);
  int32_t i_fb = float_f2i(fb), i_f = (int32_t)f;

  if (i_fb == i_f)
    return 1;

  printf("    | %9s | %8s | %8s |\n", "float", "fbits", "int");
  printf("f:  | %8f | %.8X | %.8X |\n", f, f2u(f), i_f);
  printf("fb: | %8f | %.8X | %.8X |\n", u2f(fb), fb, i_fb);

  return 0;
}

// 2.97 Compute (float) i.
static int get_order_of_magnitude(int32_t i) {
  int bits = 0;
  uint32_t bit_repr = (uint32_t)i;
  while (bit_repr != 0) {
    bit_repr >>= 1;
    bits++;
  }

  return bits - 1;
}

// static int32_t round_float_res(int32_t x) {
//   int oom = get_order_of_magnitude(x);
//   return 0;
// }

float_bits float_i2f(int32_t i) {
  float_bits exp, sign = 0, frac, E, add_one = 0, round_off = 0, round_add = 0,
                  round_frac = 0;

  E = get_order_of_magnitude(i);

  if (i == 0) {
    return 0;
  } else if (i == INT32_MIN) {
    sign = 1u << 31;
    i = INT32_MAX;
    add_one = -1; // since it's one less by absolute value
  } else if (i < 0) {
    i = -i;
    sign = 1u << 31;
    // this changes if the sign changes, need to recalculate
    E = get_order_of_magnitude(i);
  }

  // we must set i with the leftmost bit removed to occupy positions 22-0
  // 31 is sign, 30-23 is exp, 22-0 is frac
  // order of magnitude is E, thus exp is E + bias
  // special cases are 0 and INT32_MIN
  // 0 will be order of magnitude 0, but is actually exp = 0 (E = -126);
  // INT32_MIN doesn't have a positive counterpart

  int shift = FRAC_BITS - E;
  if (shift < 0) {
    uint32_t point_five, parity;

    shift = -shift;

    round_off = ~(~0x00u << (shift + 1)) & i;
    round_frac = ~(~0x00u << shift) & i;

    point_five = 1 << (shift - 1);
    parity = !!(round_off & (1 << shift));
    round_add =
        (round_frac > point_five) || ((round_frac == point_five) && (parity));

    frac = i >> (shift);
  } else {
    frac = i << shift;
  }

  frac = frac & FRAC_MASK;
  exp = (E + BIAS) << FRAC_BITS;

  return (sign | exp | frac) + round_add + add_one;
}

float true_float_i2f(int32_t i) {
  return (float)i;
}

float test_i2f(int32_t i) {
  float f = (float)i;
  float_bits fb = float_i2f(i);

  int32_t i_fb = float_f2i(fb), i_f = (int32_t)f;

  if (i_fb == i_f)
    return 1;

  printf("    | %8s | %8s | %8s |\n", "int", "fbits", "float");
  printf("f:  | %.8X | %.8X | %8f |\n", i, f2u(f), f);
  printf("fb: | %.8X | %.8X | %8f |\n", i, fb, u2f(fb));

  return 0;
}

#define test test_i2f
int main(int argc, char **argv) {
  int32_t integer;

  if (argc > 1) {
    integer = strtol(argv[1], NULL, 16);
    return !test(integer);
  }

  /*for (uint64_t i = 0x00000000; i <= UINT32_MAX; i++) {*/
  for (uint64_t i = 0x00000000; i <= UINT32_MAX; i++) {
    integer = (int32_t)i;
    if (!(test(integer)))
      return 1;
  }

  return 0;
}
