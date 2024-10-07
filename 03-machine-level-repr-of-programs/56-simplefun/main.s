A: // absolute value
  vmovsd .LC1(%rip), %xmm1
  vandpd %xmm1, %xmm0, %xmm0
.LC1:
  .long 4294967295 ;; 0xffffffff
  .long 2147483647 ;; 0x7fffffff
  .long 0
  .long 0


B: // set to 0
  vxorpd %xmm0, %xmm0, %xmm0

C: // negative
  vmovsd .LC2(%rip), %xmm1
  vxorpd %xmm1, %xmm0, %xmm0
.LC2:
  .long 0           ;; 00000000
  .long -2147483648 ;; 80000000
  .long 0
  .long 0
