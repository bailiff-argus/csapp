#define A

#ifdef A
#define EXPR(arg) ((arg) >= 0 ? (arg) : -(arg))
#elif defined(B)
#define EXPR(arg) ((arg) = 0)
#elif defined(C)
#define EXPR(arg) (-(arg))
#endif

double simplefun(double x) {
  return EXPR(x);
}
