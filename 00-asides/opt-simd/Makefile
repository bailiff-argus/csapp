CC = gcc

CPPFLAGS = -Iinc
CFLAGS = -mavx2 -pg

SRCS = src/simd.c src/vec.c
INCS = inc/vec.h inc/data.h

out: $(SRCS) $(INCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCS)
