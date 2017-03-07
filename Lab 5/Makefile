CXXFLAGS = -std=c++14 -Wall

all : test-maze genmaze

test-maze : maze.o test-maze.o testbase.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean :
	rm -f test-maze *.o *~
	rm -f genmaze.cc *.o *~

genmaze : maze.o genmaze.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY : all clean
