FC = gfortran
CC = gcc

BINS=medians omit_frame_pointer_a omit_frame_pointer_b omit_frame_pointer_c omit_frame_pointer_d omit_frame_pointer_e omit_frame_pointer_f

all: $(BINS)

omit_frame_pointer_a: omit_frame_pointer.f90
	$(FC) -O0 -fno-omit-frame-pointer -o $@ $^

omit_frame_pointer_b: omit_frame_pointer.f90
	$(FC) -O0 -fomit-frame-pointer -o $@ $^

omit_frame_pointer_c: omit_frame_pointer.f90
	$(FC) -O1 -fno-omit-frame-pointer -o $@ $^

omit_frame_pointer_d: omit_frame_pointer.f90
	$(FC) -O1 -fomit-frame-pointer -o $@ $^

omit_frame_pointer_e: omit_frame_pointer.f90
	$(FC) -O2 -fno-omit-frame-pointer -o $@ $^

omit_frame_pointer_f: omit_frame_pointer.f90
	$(FC) -O2 -fomit-frame-pointer -o $@ $^

medians: medians.c
	$(CC) -O3 -o $@ $^

clean:
	rm -f $(BINS)