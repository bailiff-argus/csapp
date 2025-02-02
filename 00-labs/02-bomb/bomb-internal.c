#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef union reg {
  uint64_t q;
  uint32_t l;
  uint16_t w;
  union {
    uint8_t lo;
    uint8_t hi;
  };
} reg_t;

void explode_bomb(void) {
  fprintf(stderr, "BOOM! Bitch\n");
  exit(EXIT_FAILURE);
}

// read six numbers puts the numbers in the memory area pointed to by rsi:
// first at rsi, second at rsi + 0x4 and so on till rsi + 0x14, filling it up till rsi + 0x18.

void phase_2(const char *str) {
  extern int nums[6];
  int *rbx, *rbp, rax;
  // read_six_numbers
  if (nums[0] != 1)
    explode_bomb();
  goto setup;

loop:
  rax = 2 * (*(rbx - 1));
  if (rax != *rbx)
    explode_bomb();
  rbx += 1;
  if (rbx == rbp)
    return;
  else
    goto loop;

setup:
  rbx = nums + 1;
  rbp = nums + 6;
}

// string: num1 num2
#define num1 0
#define num2 0

void phase_3(const char *str) {
  int rdx, rcx; // rdx -> (rsp + 8), rcx -> (rsp + 12)
  int eax = sscanf(str, "%d %d", &rdx, &rcx);
  if (eax <= 1)    // +29
    explode_bomb();

  switch (rdx) {
    case 0: eax = 0x2c3; break;
    case 1: eax = 0x137; break;
    case 2: eax = 0x2c3; break;
    case 3: eax = 0x100; break;
    case 4: eax = 0x185; break;
    case 5: eax = 0xce;  break;
    case 6: eax = 0x2aa; break;
    case 7: eax = 0x147; break;
    default: explode_bomb();
  }

  if (eax != rcx)
    explode_bomb();

  return;
}

// edi < 0x7
// called with edi, 0x0, 0xE
int func4(int edi, int esi, int edx) {
  int eax = edx - esi;     // == 0xE
  int ecx = eax >> 31;     // == 0
  eax = (eax + ecx) >> 1;  // == (0xE >> 1) == 0x7
  ecx = eax + esi;         // == 0x7
  if (ecx > edi) {         // MUST edi <= 0x7
    eax = func4(edi, esi, ecx - 1);
    eax += eax;
  } else {
    eax = 0;
    if (ecx < edi) {       // MUST edi >= 0x7
      esi = ecx + 1;
      eax = func4(edi, ecx + 1, edx);
      eax = 2 * eax + 1;
    }
  }
  
  return eax;
}

void phase_4(const char *str) {
  int edx, ecx, eax;
  eax = sscanf(str, "%d %d", &edx, &ecx);
  if (eax != 2) explode_bomb();
  if (edx > 14) explode_bomb();                // MUST edx <= 14
  if (func4(edx, 0, 0xe) != 0) explode_bomb(); // MUST edx < 7
  if (ecx != 0) explode_bomb();
  return;
}

void phase_5(const char *rdi) {
  int rax, ecx, rdx;
  const char *rbx = rdi;

  if ((rax = strlen(rdi)) != 6)
    explode_bomb();

  goto cont;

loop:
  ecx = rbx[rax];
  rdx = (char)ecx;

cont:
  rax = 0;
  goto loop;

}

// int read_six_numbers();

typedef union ptr_num {
  int64_t n;
  int *p;
} ptrnum_t;

struct node {
  uint64_t value;
  struct node *next;
};

struct node node_6 = {.value = 0x100000014c, .next = NULL};
struct node node_5 = {.value = 0x20000000a8, .next = &node_6};
struct node node_4 = {.value = 0x300000039c, .next = &node_5};
struct node node_3 = {.value = 0x40000002b3, .next = &node_4};
struct node node_2 = {.value = 0x50000001dd, .next = &node_3};
struct node node_1 = {.value = 0x60000001bb, .next = &node_2};

static volatile int *jumps[] = {
  (int *)0x6032d0,
  (int *)0x6032e0,
  (int *)0x6032f0,
  (int *)0x603300,
  (int *)0x603310,
  (int *)0x603320,
  (int *)0,
};

// str is rdi
void phase_6(const char *str) {
  extern int nums[6];
  struct node *num_ps[7];
  int *r14 = nums, *r13 = nums, *rbp = r13, r12d = 0, *rsi, *rax, *rdx, *rbx, *rcx;
  int eax, ebx, ecx, edx, esi, edi;

  r12d = 0;

  for (r12d = 0; r12d < 6; r12d++) {
    if (((unsigned) nums[r12d]) > 6)
      explode_bomb();

    for (ebx = r12d; ebx < 6; ebx++)
      if (nums[r12d] == nums[ebx])
        explode_bomb();
  }

  // up to +95: we're dealing with unique numbers 1-6

  for (int i = 0; i < 6; i++)
    nums[i] = 7 - nums[i];

  // up to +123: every number is 7 - itself

  for (esi = 0; esi < 6; esi++) {
    struct node *node = &node_1;
    for (eax = 0; eax != nums[esi] ;eax++)
      node = node->next;
    num_ps[esi] = node;
  }

  // up to +183: fill in the num_ps jump table (?),

mark_183:
  {
    struct node *b, *c, *d, **a, **end;

    b = num_ps[0];
    a = num_ps + 1;
    end = num_ps + 6;

    c = b;
  mark_201:
    d = *a;
    c->next = d;

    a++;
    if (a == end)
      goto mark_222;
    c = d;
  }

  // rearrange linked list into num_ps[0] -> num_ps[1] -> num_ps[2] -> ...

mark_222:
  {
    struct node *d = num_ps[5], *b = num_ps[0], *a;
    int bp;

    d->next = NULL;
    bp = 5;

    a = b->next;
    if (b->value < a->value)



  }

  return;
}

int main(void) {
  int x, y, z;
  printf("args=%d\n", scanf("%d %d %d", &x, &y, &z));
  return 0;
}
