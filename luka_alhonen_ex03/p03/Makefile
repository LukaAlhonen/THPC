CC = gcc
CFLAGS = -Wall

SRCS = ex3p3.c
BINS = ex3p3_O0 ex3p3_O1 ex3p3_O2 ex3p3_O3

.PHONY: all clean

all: $(BINS)

ex3p3_O0: $(SRCS)
	$(CC) $(CFLAGS) -O0 -o $@ $^

ex3p3_O1: $(SRCS)
	$(CC) $(CFLAGS) -O1 -o $@ $^

ex3p3_O2: $(SRCS)
	$(CC) $(CFLAGS) -O2 -o $@ $^

ex3p3_O3: $(SRCS)
	$(CC) $(CFLAGS) -O3 -o $@ $^

clean:
	rm -f $(BINS)
