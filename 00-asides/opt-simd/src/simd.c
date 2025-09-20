#include <vec.h>
#include <stddef.h>

/* number of bytes in a vector */
#define VBYTES 32

/* number of elements in a vector */
#define VSIZE (VBYTES / sizeof(data_t))

/* vector data type */
typedef data_t vec_t __attribute__((vector_size(VBYTES)));

data_t inner_product(vec_t av, vec_t bv) {
  long i;
  vec_t pv = av * bv;
  data_t result = 0;

  for (i = 0; i < VSIZE; i++)
    result += pv[i];

  return result;
}

void simd_v1_combine(vec_ptr v, data_t *dest) {
  long i;
  vec_t accum;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  /* Initialize all accum entries to IDENT */
  for (i = 0; i < VSIZE; i++) {
    accum[i] = IDENT;
  }

  /* Single step until have proper memory alignment */
  while ((((size_t) data) % VBYTES) != 0 && cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Step through data with VSIZE-way parallelism */
  while (cnt >= VSIZE) {
    vec_t chunk = *((vec_t *) data);
    accum = accum OP chunk;
    data += VSIZE;
    cnt -= VSIZE;
  }

  /* Single-step through the remaining elements */
  while (cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Combine elements of accumulator vector */
  for (i = 0; i < VSIZE; i++)
    result = result OP accum[i];

  /* Store result */
  *dest = result;
}

/* PROBLEMS */

#define get_chunk(from, idx) *((vec_t *) from + (idx) * VSIZE)

/* Problem 1: four sets of accumulators */
void simd_v4x4_combine(vec_ptr v, data_t *dest) {
  long i;
  vec_t acc0, acc1, acc2, acc3, acc;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  /* Initialize all accum entries to IDENT */
  for (i = 0; i < VSIZE; i++) {
    acc[i]  = IDENT;
    acc0[i] = IDENT;
    acc1[i] = IDENT;
    acc2[i] = IDENT;
    acc3[i] = IDENT;
  }

  /* Single step until have proper memory alignment */
  while ((((size_t) data) % VBYTES) != 0 && cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Step through data with VSIZE-way parallelism */
  while (cnt >= (VSIZE * 4)) {

    vec_t chunk0 = get_chunk(data, 0),
          chunk1 = get_chunk(data, 1),
          chunk2 = get_chunk(data, 2),
          chunk3 = get_chunk(data, 3);

    acc0 = acc0 OP chunk0;
    acc1 = acc1 OP chunk1;
    acc2 = acc2 OP chunk2;
    acc3 = acc3 OP chunk3;

    data += VSIZE * 4;
    cnt  -= VSIZE * 4;
  }

  /* Single-step through the remaining elements */
  while (cnt) {
    result = result OP *data++;
    cnt--;
  }

  acc = acc0 OP acc1 OP acc2 OP acc3;
  /* Combine elements of accumulator vector */
  for (i = 0; i < VSIZE; i++)
    result = result OP acc[i];

  /* Store result */
  *dest = result;
}

/* Problem 2: read 4 32-byte chunks from memory per iteration, combine with reassociation */
void simd_v4x1a_combine(vec_ptr v, data_t *dest) {
  long i;
  vec_t accum;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  /* Initialize all accum entries to IDENT */
  for (i = 0; i < VSIZE; i++) {
    accum[i] = IDENT;
  }

  /* Single step until have proper memory alignment */
  while ((((size_t) data) % VBYTES) != 0 && cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Step through data with VSIZE-way parallelism */
  while (cnt >= (VSIZE * 4)) {

    vec_t chunk0 = get_chunk(data, 0),
          chunk1 = get_chunk(data, 1),
          chunk2 = get_chunk(data, 2),
          chunk3 = get_chunk(data, 3);

    accum = accum OP
      ((chunk0 OP chunk1) OP (chunk2 OP chunk3));

    data += VSIZE * 4;
    cnt  -= VSIZE * 4;
  }

  /* Single-step through the remaining elements */
  while (cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Combine elements of accumulator vector */
  for (i = 0; i < VSIZE; i++)
    result = result OP accum[i];

  /* Store result */
  *dest = result;
}

/* Problem 3: SIMD version of inner-product */
void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;
  long length = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t sum = (data_t) 0;

  for (i = 0; i < length; i++) {
    sum = sum + udata[i] * vdata[i];
  }

  *dest = sum;
}

void simd_inner_product(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;

  long cnt = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(u);

  data_t sum = (data_t) 0;
  vec_t  accum;

  for (i = 0; i < VSIZE; i++)
    accum[i] = 0;

  /*
   * Same alignment lets us start using AVX from a certain point.
   * First we get to the point where the alignment is correct.
   */

  while (cnt && (((size_t)udata % 32) != 0)) {
    sum = sum + *udata++ * *vdata++;
    cnt--;
  }

  while (cnt >= VSIZE) {
    vec_t u_chunk = *((vec_t *)udata),
          v_chunk = *((vec_t *)vdata);
    accum = accum + (u_chunk * v_chunk);

    udata += VSIZE;
    vdata += VSIZE;
    cnt -= VSIZE;
  }

  while (cnt > 0) {
    sum = sum + *udata++ * *vdata++;
    cnt--;
  }

  for (i = 0; i < VSIZE; i++)
    sum = sum + accum[i];

  *dest = sum;
}

/* Problem 4: extend 3 to accumulate sums in 4 vectors */
void simd_v4x4_inner_product(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;

  long cnt = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(u);

  data_t sum = (data_t) 0;
  vec_t  accum, accum0, accum1, accum2, accum3;

  for (i = 0; i < VSIZE; i++) {
    accum[i] = 0;

    accum0[i] = 0;
    accum1[i] = 0;
    accum2[i] = 0;
    accum3[i] = 0;
  }

  while (cnt && (((size_t)udata % 32) != 0)) {
    sum = sum + *udata++ * *vdata++;
    cnt--;
  }

  while (cnt >= VSIZE * 4) {
    vec_t uchunk, vchunk;

#define process_chunk(accumulator)                                             \
  {                                                                            \
    uchunk = get_chunk(udata, 0);                                              \
    vchunk = get_chunk(vdata, 0);                                              \
    accumulator = accumulator + (uchunk + vchunk);                             \
    udata += VSIZE;                                                            \
    vdata += VSIZE;                                                            \
  }

    process_chunk(accum0);
    process_chunk(accum1);
    process_chunk(accum2);
    process_chunk(accum3);

    cnt -= VSIZE * 4;

#undef process_chunk
  }

  while (cnt > 0) {
    sum = sum + *udata++ * *vdata++;
    cnt--;
  }

  accum = (accum0 + accum1) + (accum2 + accum3);
  for (i = 0; i < VSIZE; i++)
    sum = sum + accum[i];

  *dest = sum;
}

/* Problem 5: 1x1 SIMD version of polynomial evaluation, unknown alignment of a */
typedef double double_vec_t __attribute__((vector_size(VBYTES)));
#define DV_SIZE (VBYTES / sizeof(double))

double poly_simd_v1x1(double a[], double x, long degree) {
  long i;
  vec_t accum;
  long cnt = degree + 1;
  double result = 0;
  double xpwr = 1.0;

  vec_t xvv;   /* x^{VSIZE} */
  vec_t xpwrv; /* Increasing powers of x */

  /* Initialize the accumulator and compute x^{VSIZE} to populate xvv later */
  for (i = 0; i < VSIZE; i++) {
    accum[i] = 0;
    xpwr *= x;
  }

  for (i = 0; i < VSIZE; i++) {
    xvv[i] = xpwr;
  }

  xpwr = 1.0;
  /* Signle step until memory alignment */
  while (((size_t) a) % VBYTES && cnt) {
    result += *a++ * xpwr;
    xpwr = xpwr * x;
    cnt--;
  }

  /* Create vector with xpwr, xpwr * x, ... */
  for (int i = 0; i < VSIZE; i++) {
    xpwrv[i] = xpwr;
    xpwr *= x;
  }

  /* Main loop. Accumulate sums in parallel. */
  while (cnt >= VSIZE) {
    vec_t a_chunk = get_chunk(a, 0);

    accum += a_chunk * xpwrv;
    xpwrv *= xvv;
    a += VSIZE;
    cnt -= VSIZE;
  }

  /* Extract accumulated values */
  for (i = 0; i < VSIZE; i++)
    result += accum[i];

  /* Single step the rest */
  xpwr = xpwrv[0];
  while (cnt) {
    result += *a++ * xpwr;
    xpwr *= x;
    cnt--;
  }

  return result;
}

/*
 * Problem 6: Using vector code, multiple accumulators, reassociation and Horner's method,
 * write fastest polynomial evaluation function.
 */

int main(void) { return 0; }
