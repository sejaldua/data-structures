/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 28/November/2018
 * Project 2: Gerp [PHASE 1]
 *
 * Filename: StringProessing.cpp
 * Contains: Driver for Project 2
 * Part of: Project 2 "Gerp" Phase 1 for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;


string strip_string(string str);


int main()
{
	// repeatedly accepts a query on standard in (cin) & calls helper function
	string str, stripped_str;
	while (cin >> str) {

		// prompts user for query string (matches spec exactly)
		cout << "Query?" << endl;
		
		stripped_str = strip_string(str);
		cout << stripped_str << endl << endl;
	}

	// cout statement on ctrl-D (matches spec exactly)
	cout << "Goodbye! Thank you and have a nice day." << endl;

	return 0;
}

// Function: strip_string
// Inputs: string str
// Returns: string
// Does: strips all leading and trailing non-alphanumeric characters 
// from the query and returns string to print to cout
string strip_string(string str)
{
	// strip leading non-alphanumeric characters
	while (!isalnum(str[0]))
		str = str.substr(1);

	// strip trailing non-alphanumeric characters
	while (!isalnum(str[str.length() - 1]))
		str = str.substr(0, str.length()-1);

	return str;
}




