; ip in %rdi, fp in %rsi, dp in %rdx, l in %rcx
fcvt2:
  movl        (%rdi), %eax          ; eax = *ip;  (i = *ip)
  vmovss      (%rsi), %xmm0         ; xmm0 = *fp; (f = *fp)
  vcvttsd2si  (%rdx), %r8d          ; r8d = (int) (*dp);
  movl        %r8d, (%rdi)          ; *ip = r8d = (int) (*dp);
  vcvtsi2ss   %eax, %xmm1, %xmm1    ; xmm1 = (float) eax = (float) *ip;
  vmovss      %xmm1, (%rsi)         ; *fp = (float) *ip;
  vcvtsi2sdq  %rcx, %xmm1, %xmm1    ; xmm1 = (double) rcx = (double) l;
  vmovsd      %xmm1, (%rdx)         ; *dp = xmm1 = (double) l;
  vunpcklps   %xmm0, %xmm0, %xmm0   ;
  vcvtps2pd   %xmm0, %xmm0          ; xmm0 = (double)xmm0;
  ret                               ; ret xmm0 = (double) f;
