Address range of 0xffffb754 <-> 0xffffd754.

A. 0xd754 - 0xb754 = 0x2000 = 2 * 16^3 = 2^13. The range is about 2^13.
B. 128-byte sled covers 2^7 bytes. 2^13 / 2^7 = 2 ^ 6 = 64.
   It would take roughly 64 attempts to hit the sled.
