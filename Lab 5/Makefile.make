CXXFLAGS = -std=c++14 -Wall

all : test-maze

test-maze : maze.o test-maze.o testbase.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f test-maze *.o *~

maze.o : maze.cc genmaze.cc
	g++ -std=c++14 -Wall -c genmaze.cc

.PHONY : all clean
