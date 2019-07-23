/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp [PHASE 2]
 *
 * Filename: main.cpp
 * Contains: driver
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Gerp.h"

using namespace std;

int main(int argc, char *argv[])
{
	// instantiate a Gerp object
	Gerp g;

	// throw an error statement if a directory path is not given
	if (argc != 2) 
	{
		cerr << "usage: " << argv[0] << " directory" << endl;
		return -1;
	}

	// populate hash from the command line directory argument
	string directory = argv[1];
	g.populate_hash(directory);

	// repeatedly accepts a query on standard in (cin)
	string str, stripped_str;
	cout << "Query? ";
	bool case_sensitive = true;
	while (cin >> str) {	
		cin.ignore();

		// if the user specifies a case insensitive query, flip bool to false
		if (str == "@i" or str == "@insensitive")
			case_sensitive = false;

		// break while loop if the user enters quit on standard in
		else if (str == "@q" or str == "@quit")
			break;

		// QUERY
		else {

			// strip leading and trailing non-alphanumeric chars from the str
			stripped_str = g.strip_string(str);

			// case sensitive query
			if (case_sensitive)
				g.query_s(stripped_str);

			// case insensitive query
			else
				g.query_i(stripped_str);

			// reset for next query
			cout << "Query? ";
			case_sensitive = true;
		}
	}

	// cout statement on ctrl-D (matches reference implementation)
	cout << endl << "Goodbye! Thank you and have a nice day." << endl;

    return 0;
}
