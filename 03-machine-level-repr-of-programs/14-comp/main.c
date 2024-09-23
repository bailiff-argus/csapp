#include <stdint.h>

// A.
// testq  %rdi, %rdi
// setge  %al
int test_a(int64_t a) { return a >= 0; }

// B.
// tesw   %di, %di
// sete   %al
int test_b(/*[u]*/ int16_t a) { return a == 0; }

// C.
// testb  %dil, %dil
// seta   %al
int test_c(uint8_t a) { return a > 0; }

// D.
// testl  %edi, %edi
// setle  %al
int test_d(int32_t a) { return a <= 0; }
