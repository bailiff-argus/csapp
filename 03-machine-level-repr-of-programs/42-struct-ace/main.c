struct ACE {
  short       v;
  struct ACE *p;
};

// A.
short test(struct ACE *ptr) {
  short ret = 1;
  while (ptr != 0) {
    ret *= ptr->v;
    ptr = ptr->p;
  }

  return ret;
}

// B. The data structure is a linked list.
//    Calculate the product of all elements.
