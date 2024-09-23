//               rdi     rsi     rdx     rcx
void switcher(long a, long b, long c, long *dest) {
  long val;

  switch (a) {
  case 5: /* L7 */
    c = b ^ 0x0f;
    /* fallthrough */

  case 0: /* L3 */
    val = c + 112;
    break;

  case 2:
  case 7: /* L5 */
    val = (c + b) << 2;
    break;

  case 4:
    val = a;
    break;

  default:
    val = b;
    break;
  }

  *dest = val;
}
