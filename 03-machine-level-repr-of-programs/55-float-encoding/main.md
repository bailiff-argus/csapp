```asm
.LC3
  .long 0          ;; 0x00000000
  .long 1077936128 ;; 0x40400000
```

The resulting float is represented by the following byte structure:
```
40 40 00 00 00 00 00 00
```

A double precision float has:
- 1 sign bit (63),
- 11 exponent bits (62-52),
- 52 fraction bits.

The exponent is biased by 1023.
32 is 2^5.
Accounting for bias, the resulting exponent value is 1028, or 1024 + 4.
The fractional part must be all zeroes.
The sign bit must be zero.

From `40 40`, the exponent bit pattern is: `10000000100`, which is precisely 1028.
Thus, the number is `+1 * 2 ^ (1028 - 1023) * 1.0 = 32.0`.
