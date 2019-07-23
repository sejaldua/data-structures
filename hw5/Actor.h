/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: Actor.h
 * Contains: Interface of the Actor class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */


#include "LinkedList.h"
using namespace std;

class Actor
{

public:

	Actor();
	Actor(string actor_name);

	string get_name() const;				//getter for Actor name			
	void insert_movie(string movie);		//insert movie function
	bool check_movie(string movie) const;	//check movie function
	string connect(Actor a) const;			//compare movies and try to connect 

	// friend functions for overload operators
	friend bool operator == (const Actor &a1, const Actor &a2);
	friend bool operator != (const Actor &a1, const Actor &a2);
	friend ostream &operator << (ostream &os, const Actor &a);

private:
	string name;
	LinkedList<string> movies;

};

