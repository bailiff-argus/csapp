//                 %rdi    %rsi
long switch_prob(long x, long n) {
  long result = x;

  switch(n) {
    case 0: case 2:
      result = x * 8;
      break;

    case 3:
      result = x >> 3;
      break;

    case 4:
      x = (x << 4) - x;
    case 5:
      x *= x;
    case1: default:
      result = x + 0x4b;
      break;
  }

  return result;
}
