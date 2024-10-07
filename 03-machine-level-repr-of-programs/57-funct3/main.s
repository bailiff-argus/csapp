funct3:
  vmovss       (%rdx), %xmm1         ;; xmm1 = *dp
  vcvtsi2sd    (%rdi), %xmm2, %xmm2  ;; xmm2 = (double)(*ap)
  vucomisd     %xmm2, %xmm0          ;; b VS xmm2
  jbe          .L8                   ;; if b > xmm2
  vcvtsi2ssq   %rsi, %xmm0, %xmm0    ;;   xmm0 = c
  vmulss       %xmm1, %xmm0, %xmm1   ;;   xmm1 = d * c
  vunpcklps    %xmm1, %xmm1, %xmm1   ;;
  vcvtps2pd    %xmm1, %xmm0          ;;
  ret                                ;;   return (double)xmm1

.L8                                  ;; else
  vaddss       %xmm1, %xmm1, %xmm1   ;;   xmm1 += xmm1
  vcvtsi2ssq   %rsi, %xmm0, %xmm0    ;;   xmm0 = (float)c
  vaddss       %xmm1, %xmm0, %xmm0   ;;   xmm0 = xmm0 + xmm1
  vunpcklps    %xmm0, %xmm0, %xmm0   ;;   
  vcvtps2pd    %xmm0, %xmm0          ;;   return (double)xmm0
  ret
