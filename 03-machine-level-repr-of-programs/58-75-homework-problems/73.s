	.globl	find_range_asm
find_range_asm:
	vxorps    %xmm1, %xmm1, %xmm1
	vucomiss	%xmm0, %xmm1
	jp        .nan
	jb        .gz
	je        .z
	ja        .lz
.lz:
	mov      $0, %eax
	ret
.z:
	mov      $1, %eax
	ret
.gz:
	mov      $2, %eax
	ret
.nan:
	mov      $3, %eax
	ret
