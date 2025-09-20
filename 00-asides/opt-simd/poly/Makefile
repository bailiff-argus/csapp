CC = gcc

CPPFLAGS = -Iinc

ifdef RELEASE
  OPT := -O3
else
  OPT := -O0 -pg
endif

CFLAGS = -Wall -Werror -mavx2 $(OPT) -ggdb3

SRCS = src/main.c src/poly.c
INCS = inc/poly.h

test_poly: $(SRCS) $(INCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCS)

clean:
	rm -f test_poly
