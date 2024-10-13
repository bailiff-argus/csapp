c_imag:
  movapd   %xmm1, %xmm0
  ret

c_real:
  rep; ret

c_sub:
  subsd   %xmm2, %xmm0
  subsd   %xmm3, %xmm1
  ret
