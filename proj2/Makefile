

CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2
DEPS = DirNode.h FSTree.h Hash.h Entry.h
 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

gerp: main.o Gerp.o Hash.o DirNode.o FSTree.o Entry.o
	$(CC) -o $@ $^

clean: 
	rm -f main.o Gerp.o Hash.o Entry.o core* *~ 

provide:
	provide comp15 gerp-phase2 main.cpp Makefile Gerp.h Gerp.cpp Hash.h \
	Hash.cpp DirNode.h DirNode.o FSTree.h FSTree.o Entry.cpp Entry.h README