funct2:
  vcvtsi2ss     %edi, %xmm2, %xmm2    ;; xmm2 = (float)x;
  vmulss        %xmm1, %xmm2, %xmm1   ;; y = x * y;
  vunpcklps     %xmm1, %xmm1, %xmm1   ;; 
  vcvtps2pd     %xmm1, %xmm2          ;; xmm2 = (double)(y*x);
  vcvtsi2sdq    %rsi, %xmm1, %xmm1    ;; xmm1 = (double)z;
  vddivsd       %xmm1, %xmm0, %xmm0   ;; xmm0 = w / z;
  vsubsd        %xmm0, %xmm2, %xmm0   ;; xmm0 = xmm2 - xmm0 = y*x - z/w;
  ret
