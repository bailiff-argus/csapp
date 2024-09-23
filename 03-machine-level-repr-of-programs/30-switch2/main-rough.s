.L4:
	.quad .L9 // -2
	.quad .L5 // -1
	.quad .L6 // 0
	.quad .L7 // 1
	.quad .L2 // 2
	.quad .L7 // 3
	.quad .L8 // 4
	.quad .L2 // 5
	.quad .L5 // 6

switch2:
	addq $2, %rdi        // x + 2
	cmpq $8, %rdi        // x vs 8
	ja   .L2             // x > 8 -> .L2 (default)
	jmp  *.L4(, %rdi, 8) // 8(x + 2)
