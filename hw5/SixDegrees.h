/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: SixDegrees.h
 * Contains: Interface of the SixDegrees class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "Actor.h"
#include "Graph.h"

#ifndef SIX_DEGREES_H_
#define SIX_DEGREES_H_

using namespace std;


class SixDegrees
{
public:
	SixDegrees();
	int count_asterisks() const;
	void parse_and_populate();
	void run(istream &in, ostream &out);
	void BFS(Actor a, Actor b, ostream &out);

private:
	int num_actors;
	Graph<Actor> g;

};

#endif