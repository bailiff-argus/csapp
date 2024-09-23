.file "main.s"
.text

zero_xor:
  xorq %rax, %rax

zero_mov:
  movq $0, %rax
