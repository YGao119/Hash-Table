CXX=g++
CXXFLAGS=-g -Wall -std=c++11

all: counting

counting: counting.cpp Hashtable.o
	$(CXX) $(CXXFLAGS) $^ -o counting

Hashtable.o: Hashtable.cpp Hashtable.h
	$(CXX) $(CXXFLAGS) $< -c -o Hashtable.o
	

clean:
	rm -f counting Hashtable.o
