CXX=g++
CXXFLAGS=-Wall -g -pg -std=c++11

Program : Main.cpp Dictionary.h
	$(CXX) $(CXXFLAGS) Main.cpp -o $@

gmon.out : Program
	./Program

.PHONY : clean prof

clean:
	rm -f *.o Program *.out

prof : gmon.out Program
	gprof -p -b Program

