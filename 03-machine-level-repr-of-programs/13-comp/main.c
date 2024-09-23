#include <stdint.h>

// A.
// cmpl %esi, %edi
// setl %al
int comp_a(/*u*/ int32_t a, /*u*/ int32_t b) { return a < b; }

// B.
// cmpw  %si,%di
// setge %al
int comp_b(int16_t a, int16_t b) { return a >= b; }

// C.
// cmpb  %sil, %dil
// setbe %al
int comp_c(uint8_t a, uint8_t b) { return a <= b; }

// D.
// cmpq  %rsi, %rdi
// setne %a
int comp_d(/*u*/ int64_t a, /*u*/ int64_t b) { return a != b; }
