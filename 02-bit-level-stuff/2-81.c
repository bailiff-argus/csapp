int A(int k) {
  return -1 << k;
}

int B(int k, int j) {
  return ~A(k) << j;
}
