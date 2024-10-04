#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *gets(char *s) {
  int c;
  char *dest = s;

  while ((c = getchar()) != '\n' && c != EOF)
    *dest++ = c;

  if (c == EOF && dest == s)
    return NULL;

  *dest++ = '\0';
  return s;
}

// -> 0123456789012345678901234
char *get_line() {
  char buf[4];
  char *result;

  gets(buf);

  result = malloc(strlen(buf));
  strcpy(result, buf);
  return result;
}
