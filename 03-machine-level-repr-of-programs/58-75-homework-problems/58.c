//             %rdi    %rsi    %rdx
long decode2(long x, long y, long z) {
#ifdef BRUTE
  y -= z;
  x *= y;
  y = (y << 63) >> 63; // if y is odd, all 1s. Else, all 0s.
  return x ^ y;
#else
  return ((y - z) % 2) ? ~x : x;
#endif
}
