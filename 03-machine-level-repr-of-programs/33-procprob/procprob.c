// procprob:
//   movslq   %edi, %rdi    ; edi is an int that's promoted to a long
//   addq     %rdi, (%rdx)  ; rdx is a pointer to a long
//   addb     %sil, (%rcx)  ; rcx is a pointer to a byte
//   movl     $6, %eax      ; since total sizeof is 6, there's an int and a short int
//   ret

//                  edi      si     rdx     rcx
// TYPE procprob(TYPE _, TYPE _, TYPE _, TYPE _) {
//   *u += a; *(char *) += char ->  or vice versa
//   *v += b; *(long *) += long ----^
//   return sizeof(a) + sizeof(b); (4 + 2, int and short)

int procprob(int a, short b, long *u, char *v);
// OR
int procprob2(int b, short a, long *v, char *u);
