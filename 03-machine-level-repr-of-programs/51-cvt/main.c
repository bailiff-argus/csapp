#define dest_t int
#define src_t int

dest_t cvt(src_t x) {
  dest_t y = (dest_t) x;
  return y;
}

#undef dest_t
#undef src_t

//  src_t      dst_t       instructions
//  long       double     vcvtsi2sdq   %rdi, %xmm0, %xmm0
// double       int       vcvttsd2si   %xmm0, %eax
// double      float      vunpcklpd    %xmm0, %xmm0, %xmm0
//                        vcvtpd2ps    %xmm0, %xmm0
//  long       float      vcvtsi2ssq   %rdx, %xmm0, %xmm0
// float       long       vcvttss2siq  %xmm0, %rax
