struct test {
  short *p;
  struct {
    short x;
    short y;
  } s;
  struct test *next;
};

void st_init(struct test *st) {
  st->s.y  = st->s.x;
  st->p    = &(st->s.y);
  st->next = st;
}

// A. Offsets of fields in bytes:
//    p: 0
//  s.x: 8
//  s.y: 10
// next: 12
//
// B. Total bytes: 20
