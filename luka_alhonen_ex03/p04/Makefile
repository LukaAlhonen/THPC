CC = gcc -lm -g
CFLAGS = -Wall

BINS = p04_cpu p04_wall

.PHONY: all clean

all: $(BINS)

p04_cpu: p04_cpu.c
	$(CC) $(CFLAGS) -o $@ $^

p04_wall: p04_wall.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BINS)