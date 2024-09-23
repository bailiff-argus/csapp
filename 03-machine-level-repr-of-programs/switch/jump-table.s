.section .rodata
.align   8

.L4:
	.quad .L3
	.quad .L8
	.quad .L5
	.quad .L6
	.quad .L7
	.quad .L8
	.quad .L7

	// ...

switch_eg:
	subq $100, %rsi
	cmp  %rsi, 6
	ja   .L8
	jmp  *.L4(, %rsi, 8)

.L3:  // loc_A / case 100
	leaq (%rdi, %rdi, 2), %rax // 3x
	leaq (%rdi, %rax, 4), %rdi // 13x
	jmp  .L2

.L5:
	addq $10, %rdi

.L6:
	addq $11, %rdi
	jmp  .L2

.L7:
	imulq %rdi, %rdi
	jmp   .L2

.L8:
	movq $0, %rdi

.L2:
	movq %rdi, (%rdx)
	ret
