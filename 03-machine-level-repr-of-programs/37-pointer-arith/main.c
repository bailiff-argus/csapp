#include <stdlib.h>

int main(void) {
  short P[100];
  long i = rand() % 100;

  //      Expression          Type        Value               Assembly code
  (void)( P[1]       ); //   short       M[Xp + 2]           movw   2(%rdx),%ax
  (void)( P + 3 + i  ); //   short *     Xp + 6 + i*2        leaq   6(%rdx,%rcx,2),%rax
  (void)( P[i*6 - 5] ); //   short       M[Xp + 12*i - 10]   movw   -10(%rdx,%rcx,12),%ax
  (void)( P[2]       ); //   short       M[Xp + 4]           movw   4(%rdx),%ax
  (void)( &P[i + 2]  ); //   short *     Xp + i*2 + 4        leaq   4(%rdx,%rcx,2),%rax
}
