// I assume this is about branch prediction, but both compile
// to branching with every optimization option for me.

long cread(long *xp) {
  return (xp ? *xp : 0);
}

long cread_alt(long *xp) {
  return (!xp ? 0 : *xp);
}
