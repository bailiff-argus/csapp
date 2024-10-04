```c
char *get_line() {
  char buf[4];
  char *result;

  gets(buf);

  result = malloc(strlen(buf));
  strcpy(result, buf);
  return result;
}
```

```asm
00400720 <get_line>:
  400720:   53              push   %rbx
  400721:   48 83 ec 10     sub    $0x10, %rsp
> diagram stack is here
  400725:   48 89 e7        mov    %rsp, %rdi
  400728:   e8 73 ff ff ff  callq  4006a0 <gets>
> modify stack here
```

A.     diagram stack
| 00 00 00 00 00 40 00 76 | < Return address
| 01 23 45 67 89 AB CD EF | < %rbx
| 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 00 00 00 | < stack top

After entering 0123456789012345678901234

B.     modify stack
| 00 00 00 00 00 40 00 34 | < Return address (corrupted)
| 33 32 31 30 39 38 37 36 | < %rbx (corrupted)
| 35 34 33 32 31 30 39 38 |
| 37 36 35 34 33 32 31 30 | < stack top

C. The program attempts to return to addr 00400034.
D. %rbx becomes corrupted after get_line returns.
E. Malloc result isn't checked, and it should have strlen(buf) + 1.
