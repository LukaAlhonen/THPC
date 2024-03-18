CC = gcc

BINS = p01_formatted_O0 p01_formatted_O3 p01_unformatted_O0 p01_unformatted_O3 medians

all: $(BINS)

p01_formatted_O0: p01_formatted.c
	$(CC) -o p01_formatted_O0 p01_formatted.c -O0

p01_formatted_O3: p01_formatted.c
	$(CC) -o p01_formatted_O3 p01_formatted.c -O3

p01_unformatted_O0: p01_unformatted.c
	$(CC) -o p01_unformatted_O0 p01_unformatted.c -O0

p01_unformatted_O3: p01_unformatted.c
	$(CC) -o p01_unformatted_O3 p01_unformatted.c -O3

medians: medians.c
	$(CC) -o medians medians.c -O3

clean:
	rm -f $(BINS)