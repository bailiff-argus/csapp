funct1:
  vcvtsi2ssq     %rsi, %xmm2, %xmm2
  vaddss         %xmm0, %xmm2, %xmm0   ;; q + r
  vcvtsi2ss      %edi, %xmm2, %xmm2
  vdivss         %xmm0, %xmm2, %xmm0   ;; p / (q + r)
  vunpcklps      %xmm0, %xmm0, %xmm0
  vcvtps2pd      %xmm0, %xmm0          ;; (double) (p / (q + r))
  vsubsd         %xmm0, %xmm1, %xmm0   ;; ^ - s
  ret

;; since s required no conversion, it's definitely double
;; p is definitely an int, since it's converted from %edi before division
;; either q or r must be the long converted in the beginning
;; the leftover (r or q) must be a single precision float
