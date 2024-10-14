	.globl	tmult_ok_asm
tmult_ok_asm:
	imulq	  %rsi, %rdi
	movq	  %rdi, (%rdx)
# Deleted code
# testq	  %rdi, %rdi
# setg    %al
# Inserted code:
	setae   %al
	movzbl	%al,  %eax
	ret

  .globl  umult_ok_asm
umult_ok_asm:
	movq    %rdx, %rcx
	movq    %rsi, %rax
	mulq    %rdi
	movq    %rax, (%rcx)
	setae   %al
	movzbl	%al,  %eax
	ret
