# Makefile for the biologist's grep
# Project 1
# Sejal Dua
# Comp 15 
# Fall 2018

CXX      = clang++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
LDFLAGS  = -g

SeqMatch: main.o Trie.o
	${CXX} ${LDFLAGS} -o SeqMatch main.o Trie.o

test: Test.o Trie.o
	${CXX} ${LDFLAGS} -o test Test.o Trie.o

main.o:              main.cpp Trie.h
Trie.o:  			 Trie.cpp Trie.h
Test.o:				 Test.cpp Trie.h

valgrind:  SeqMatch
	valgrind ./SeqMatch

clean:
	rm -rf proj1 *.o *.dSYM

provide:
	provide comp15 proj1 main.cpp Trie.cpp Trie.h Test.cpp README Makefile