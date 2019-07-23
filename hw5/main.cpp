/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[])
{
	SixDegrees sd;

	// run interactive mode
	if (argc == 1)
	    sd.run(cin, cout);  

	// run file-based mode
	else if (argc == 2) {
		ifstream infile;
		string filename = argv[1];
	    infile.open(filename);
	    if (!infile.is_open()) {
	    	cout << "Could not open " << filename << " for reading." << endl;
	        exit(1);
	    }
	    sd.run(infile, cout);
	    infile.close();
	}

	// throw error
	else {
		cerr << "You gave me more than 1 parameter." << endl;
		return 1;
	}
 
    return 0;
}
