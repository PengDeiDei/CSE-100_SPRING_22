# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=TestSanity

all: $(OUTFILES)

TestSanity: TestSanity.cpp CountMinSketch.cpp CountMinSketch.h BloomFilter.cpp BloomFilter.h HashFunctions.cpp HashFunctions.h
	$(CXX) $(CXXFLAGS) -o TestSanity TestSanity.cpp CountMinSketch.cpp BloomFilter.cpp HashFunctions.cpp

clean:
	$(RM) $(OUTFILES) *.o
