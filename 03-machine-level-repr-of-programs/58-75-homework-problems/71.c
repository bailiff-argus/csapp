#include <stdio.h>

void good_echo() {
  char buf[8];
  while((fgets(buf, 8, stdin) != NULL) && (buf[0] != '\n'))
    for (int i = 0; i < 8 - 1; i++) {
      char ch = buf[i];
      putc(ch, stdout);
      if ((ch == '\n') || (ch == '\0'))
        return;
    }
}
