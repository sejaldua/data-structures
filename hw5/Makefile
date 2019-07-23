

CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11
DEPS = Graph.h Queue.h Stack.h
 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

sixdegrees: main.o Graph.o Queue.o Stack.o LinkedList.o Actor.o SixDegrees.o
	$(CC) -o $@ $^

graphtest: test-graph.o Graph.o Queue.o Stack.o LinkedList.o Actor.o \
SixDegrees.o
	$(CC) -o $@ $^

clean:
	rm -f *.o core* *~ sixdegrees

provide:
	provide comp15 hw5 main.cpp Makefile Graph.h Graph.cpp Actor.h Actor.cpp \
	SixDegrees.h SixDegrees.cpp test-graph.cpp README