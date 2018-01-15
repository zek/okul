CXX=g++
CXXFLAGS=-std=c++14 -Wall -g

Iterator : Main.cpp People.h
	$(CXX) $(CXXFLAGS) Main.cpp -o $@

.PHONY: clean

clean:
	rm -f *.o Iterator
