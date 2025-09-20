#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef long data_t;
#define IDENT 0
#define OP +

typedef struct {
  long len;
  data_t *data;
} vec_rec, *vec_ptr;

// 5.9 Merge
void merge(long src1[], long src2[], long dest[], long n) {
  long i1 = 0;
  long i2 = 0;
  long id = 0;

#if 0
  while (i1 < n && i2 < n) {
    if (src1[i1] < src2[i2])
      dest[id++] = src1[i1++];
    else
      dest[id++] = src2[i2++];
  }
#endif

  while (i1 < n && i2 < n) {
    long v1 = src1[i1], v2 = src2[i2];
    long take_first = v1 <= v2;
    dest[id++] = take_first ? v1 : v2;
    i1 += take_first;
    i2 += !take_first;
  }

  while (i1 < n)
    dest[id++] = src1[i1++];

  while (i2 < n)
    dest[id++] = src2[i2++];
}

// 5.17 memset
void *memset(void *s, int c, size_t n);

void *basic_memset(void *s, int c, size_t n) {
  size_t cnt = 0;
  unsigned char *schar = s;

  while (cnt < n) {
    *schar++ = (unsigned char)c;
    cnt++;
  }

  return s;
}

#define K sizeof(unsigned long)
#define U(ptr) ((unsigned long)ptr)
void *optimized_memset(void *s, int c, size_t n) {
  unsigned char *schar = s;
  size_t cnt = 0;
  unsigned long wc;

  for (unsigned long i = 0; i < K; i++) {
    ((unsigned char *)&wc)[i] = c & 0xff;
  }

  while ((U(schar) % K) && (cnt < n)) {
    *schar++ = (unsigned char)c;
    cnt++;
  }

  while ((cnt + (K - 1)) < n) {
    *(unsigned long *)schar = wc;
    schar += K;
    cnt += K;
  }

  while (cnt < n) {
    *schar++ = (unsigned char)c;
    cnt++;
  }

  return s;
}

// 5.18 prefix sum
void psum1(float a[], float p[], long n) {
  long i;
  float last_val, val;

  last_val = p[0] = a[0];
  for (i = 1; i < n; i++) {
    val = last_val + a[i];
    p[i] = val;
    last_val = val;
  }
}

void psum2x1a(float a[], float p[], long n) {
  long i;
  float last_val, val;

  last_val = p[0] = a[0];
  for (i = 1; i < n; i++) {
    val = last_val + (a[i] + a[i+1]);
    p[i] = last_val + a[i];
    p[i+1] = val;
    last_val = val;

    // critical path is last_val->last_val with FP add chain of length 1
    // (last_val -> val, store at last_val), making the theoretical CPE 3 / 2 = 1.5
  }
}

void psum4x1a_v1(float a[], float p[], long n) {
  long i;
  float tmp1, tmp2, last_val;

  last_val = p[0] = a[0];
  for (i = 1; i+3 < n; i+=4) {
    tmp1 = last_val + a[i];
    tmp2 = tmp1 + (a[i+1] + a[i+2]);

    p[i]   = tmp1;
    p[i+1] = tmp1 + a[i+1];
    p[i+2] = tmp2;
    p[i+3] = last_val = tmp2 + a[i+3];

    // critical path is last_val->last_val with FP add chain of length 3
    // (last_val -> tmp1 -> tmp2 -> last_val), making the theoretical CPE
    // (3 * 3) / 4 = 2.25
  }

  for (; i < n; i++) {
    p[i] = p[i-1] + a[i];
  }
}

void psum4x1a_v2(float a[], float p[], long n) {
  long i;
  float tmp1, tmp2, last_val;

  last_val = p[0] = a[0];
  for (i = 1; i+3 < n; i+=4) {
    tmp1 = last_val + (a[i] + a[i+1]);
    tmp2 = tmp1 + (a[i+2] + a[i+3]);

    p[i]   = last_val + a[i];
    p[i+1] = tmp1;
    p[i+2] = tmp1 + a[i+3];
    p[i+3] = tmp2;

    // critical path is last_val->last_val with FP add chain of length 2
    // (last_val -> tmp1 -> tmp2, store at last_val), making the theoretical CPE
    // (2 * 3) / 4 = 1.5
  }

  for (; i < n; i++) {
    p[i] = p[i-1] + a[i];
  }
}

int main(void) {
  unsigned char buf[256] = {0};

  for (int c = 0; c < 256; c++) {
    optimized_memset(buf, c, c);

    for (int j = 0; j < c; j++) {
      assert(buf[j] == c);
    }

    for (int j = c; j < 256; j++) {
      assert(buf[j] == 0);
    }

    printf("All good for char %c\n", c);
  }

  return 0;
}
