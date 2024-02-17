CXX = g++
CFLAGS = -Wall -std=c++11

all: p02_O0 p02_O3

p02_O0: p02.cpp
	$(CXX) $(CFLAGS) -O0 -o p02_O0 p02.cpp

p02_O3: p02.cpp
	$(CXX) $(CFLAGS) -O3 -o p02_O3 p02.cpp

clean:
	rm -f p02_O0 p02_O3