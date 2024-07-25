# Makefile
CXX = g++
CXXFLAGS = -O3 -std=c++11

all: serial parallel

serial: main_serial.cpp
	$(CXX) $(CXXFLAGS) -o nbody_serial main_serial.cpp

parallel: main_parallel.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o nbody_parallel main_parallel.cpp

clean:
	rm -f nbody_serial nbody_parallel

