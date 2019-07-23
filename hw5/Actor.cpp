/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: Actor.cpp
 * Contains: Implementation of the Actor class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "Actor.h"
using namespace std;

// Function: default constructor
// Inputs: none
// Returns: none
// Does: instantiates an Actor object with a default name
Actor::Actor() 
{
	name = "Anonymous Actor";
}

// Function: parameterized constructor
// Inputs: string actor_name
// Returns: none
// Does: assigns actor_name to private member variable of the Actor
Actor::Actor(string actor_name) 
{
	name = actor_name;
}

// Function: get_name
// Inputs: none
// Returns: string
// Does: getter for Actor name
string Actor::get_name() const
{
	return name;
}

// Function: insert_movie
// Inputs: string movie
// Returns: none
// Does: inserts the passed in movie into the Actor's linked list of movies
void Actor::insert_movie(string movie)
{
	movies.insert(movie);
}

// Function: check_movie
// Inputs: string movie
// Returns: bool value
// Does: returns true if the given movie is in Actor's linked list of movies
bool Actor::check_movie(string movie) const
{
	bool found;
	movies.find(movie, found);
	return found;
}

// Function: connect
// Inputs: Actor object called a
// Returns: string movie name
// Does: returns the name of a movie in which the Actor object and
// Actor argument have appeared. (Note: If the Actors have no movies
// in common, an empty string is returned; if they have multiple in common,
// any one of the movies is returned.
string Actor::connect(Actor a) const
{
	int num_movies = movies.get_length();
	int i = 0;

	// index-traverse through LL of movies
	while (i < num_movies)
	{
		string curr_movie = movies.get_value_at(i);

		// check if passed in actor a has curr_movie in common
		bool found;
		(a.movies).find(curr_movie, found);
		if (found)
			return curr_movie;

		i++;
	}
	
	return "";
}


// OVERLOADED OPERATORS

// Function: operator (==)
// Inputs: const Actor object (passed in by reference)
// Returns: bool value
// Does: returns true if the actors have identical attributes, false otherwise
bool operator == (const Actor &a1, const Actor &a2)
{
	return (a1.name == a2.name);
}

// Function: operator (!=)
// Inputs: const Actor object (passed in by reference)
// Returns: bool value
// Does: returns true if the actors are not identical, false otherwise
bool operator != (const Actor &a1, const Actor &a2)
{
	return !(a1.name == a2.name);
}

// Function: operator (<<)
// Inputs: const Actor object (passed in by reference)
// Returns: a string
// Does: prints the name of the actor
ostream &operator << (ostream& os, const Actor &a)
{
	os << a.name;
	return os;
}


