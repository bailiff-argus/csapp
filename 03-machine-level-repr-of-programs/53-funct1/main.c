#define arg1_t int
#define arg2_t long
#define arg3_t float
#define arg4_t double

// arg2_t and arg3_t can switch places

double funct1(arg1_t p, arg2_t q, arg3_t r, arg4_t s) {
  return p/(q+r) - s;
}
