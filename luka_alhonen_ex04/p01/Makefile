CXX = g++
CFLAGS = -Wall -std=c++11 -O3

all: p01_a p01_a_optimised p01_b p01_b_optimised

p01_a: p01_a.cpp
	$(CXX) $(CFLAGS) -o p01_a p01_a.cpp

p01_a_optimised: p01_a_optimised.cpp
	$(CXX) $(CFLAGS) -o p01_a_optimised p01_a_optimised.cpp

p01_b: p01_b.cpp
	$(CXX) $(CFLAGS) -o p01_b p01_b.cpp

p01_b_optimised: p01_b_optimised.cpp
	$(CXX) $(CFLAGS) -o p01_b_optimised p01_b_optimised.cpp

clean:
	rm -rf p01_a p01_a_optimised p01_b p01_b_optimised