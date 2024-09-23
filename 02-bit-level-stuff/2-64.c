// for any given byte: 0101 8*0 + 4*1 + 2*0 + 1*1 = 5

int any_odd_one(unsigned x) {
  return (x & 0x55555555) != 0;
}
