#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

size_t size_t_mult_ok(size_t x, size_t y) {
  size_t p = x * y;
  return !x || p / x == y;
}

void *my_calloc(size_t nmemb, size_t size) {
  void *buf;
  size_t len;

  if ((nmemb == 0) || (size == 0))
    return NULL;

  if (!size_t_mult_ok(nmemb, size))
    return NULL;

  len = nmemb * size;
  buf = malloc(len);
  if (buf == NULL)
    return NULL;

  memset(buf, 0, len);

  return buf;
}
