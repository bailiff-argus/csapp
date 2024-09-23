.L4:
	.quad .L3 // 0
	.quad .L2 // 1 DEF
	.quad .L5 // 2
	.quad .L2 // 3 DEF
	.quad .L6 // 4
	.quad .L7 // 5
	.quad .L2 // 6 DEF
	.quad .L5 // 7

	// ...

switcher:
	cmpq $7, %rdi
	ja   .L2
	jmp  *.L4(, %rdi, 8)

.L7:
	xorq $15, %rsi
	movq %rsi, %rdx

.L3:
	leaq 112(%rdx), %rdi
	jmp  .L6

.L5:
	leaq (%rdx, %rsi), %rdi
	salq ($2, %rdi)
	jmp  .L6

.L2:
	movq %rsi, %rdi

.L6:
	movq %rdi, (%rcx)
	ret
