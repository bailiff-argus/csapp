typedef union {
  struct {
    long u;
    short v;
    char w;
  } t1;
  struct {
    int   a[2];
    char *p;
  } t2;
} u_type;

#define expr up->t1.u
#define type long
// movq   (%rdi), %rax
// movq   %rax, (%rsi)

// #define expr up->t1.v
// #define type short
// movw   8(%rdi), %ax
// movw   %ax, (%rsi)

// #define expr &up->t1.w
// #define type char *
// addq   $10, %rdi
// movq   %rdi, (%rsi)

// #define expr up->t2.a
// #define type int *
// movq   %rdi, (%rsi)

// #define expr up->t2.a[up->t1.u]
// #define type int
// movq   (%rdi), %rax
// movl   (%rdi,%rax,4), %eax
// movl   %eax, (%rsi)

// #define expr *up->t2.p
// #define type char
// movq   8(%rdi), %rax
// movb   (%rax), %al
// movb   %al, (%rsi)

void get(u_type *up, type *dest) {
  *dest = expr;
}
