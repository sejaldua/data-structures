/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: SixDegrees.cpp
 * Contains: Implementation of the SixDegrees class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

// Function: default constructor
// Inputs: none
// Returns: none
// Does: instantiates a new SixDegrees object and initializes graph private
// member variable to have the same number of vertices as number of astersisks
// in the file, finally parses the file and populates the graph g
SixDegrees::SixDegrees()
{
	num_actors = count_asterisks();
	g.initialize_graph(num_actors);
	parse_and_populate();
}

// Function: count_asterisks
// Inputs: none
// Returns: none
// Does: parses through file, incrementing a counter every time the getline
// function stores the string "*"  (Note: this will tell us the number of 
// vertices (actors) we will need in our graph)
int SixDegrees::count_asterisks() const
{
	ifstream infile;
	infile.open("actors.txt");
	string line = "";
	int asterisk_count = 0;
	while(getline(infile, line)) {
		if (line == "*")
			asterisk_count++;
	}
	infile.close();
	return asterisk_count;
}

// Function: parse_and_populate
// Inputs: none
// Returns: none
// Does: parses the actors files, instantiating new actor objects, inserting
// movie titles into the actor's linked list of movies, and finally adding 
// the recently created actor as a vertex in the graph g; after all vertices
// have been inserted, we iterate through the array of actors just created
// from the parsing process and establish symmetric edges (connections) 
// between actors
void SixDegrees::parse_and_populate()
{
	ifstream infile;							// ifstream obj
	infile.open("actors.txt");					// hard-coded		
	string line = "";							// initialize line
	Actor a;									// instantiate Actor obj
	int index = 0;								// indexing var
	Actor actors[num_actors];					// storage array of actors
	bool flag = true;							// bool flag (actor vs. movie)
	while(getline(infile, line)) {

		// have gathered all of actor's info, add actor to graph, flip bool
		if (line == "*") {
			actors[index] = a;
			index++;
			g.add_vertex(a);
			flag = true;
		}
		// gather actor information
		else {
			if (flag) {
				a = Actor(line);
				flag = false;
			}
			else
				a.insert_movie(line);
		}
	}

	// establish edges
	for (int i = 0; i < num_actors - 1; i++) {
		for (int j = i + 1; j < num_actors; j++) {
			string connection = actors[i].connect(actors[j]);
			if (connection != "")
				g.add_edge(actors[i], actors[j], connection);
		}
	}
}

// Function: run
// Inputs: istream object in, ostream object out
// Returns: none
// Does: continually prompts for the name of two actors via getline function
// makes actors from strings, checks if they are actual vertices in the graph,
// and then runs BFS algorithm on the two actors
void SixDegrees::run(istream &in, ostream &out) 
{
	string start, end;
	out << "Enter two actor names separated by a new line." << endl;
	out << "Press ctrl-D to quit" << endl;
	while (getline(in, start) && getline(in, end)) {
		Actor a1(start);
		Actor a2(end);
		if (!g.is_vertex(a1)) {
			out << "Sorry, " << start << " is not in the list." << endl;
			out << endl;
		}
		else if (!g.is_vertex(a2))
			out << "Sorry, " << end << " is not in the list." << endl << endl;
		else 
			BFS(a1, a2, out);
	}
}

// Function: BFS
// Inputs: 2 Actors a and b, ostream object out (passed in by reference)
// Returns: none
// Does: trampoline function for BFS algorithm
void SixDegrees::BFS(Actor a, Actor b, ostream &out) 
{
	g.BFS(a, b, out);
}

