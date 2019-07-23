/* 
 * Station.cpp
 * Sejal Dua
 * 24/September/2018
 * COMP15 HW2
 * Fall 2018
 *
 * Implementation of the Station class for homework 2
 */

#include "Station.h"

// Constructor
Station::Station()
{
	name = "NoName";
    access = false;
}

// Parameterized Constructor: 
	// string containing station name
	// boolean about accessibility 
Station::Station(string input_name, bool input_access)
{
    name = input_name;
    access = input_access;
}

// Function: is_equal
// Input: Station object
// Returns: boolean
// Does: evaluates whether or not the station contains the 
// same information as the passed in station object
bool Station::is_equal(Station s)
{
    if (s.name == name && s.access == access)
    	return true;
    else
    	return false;
}

// Function: print
// Input: ostream address
// Returns: none
// Does: prints a string containing a square bracket, the station name,
// and an A or U to indicate if accessibility options are available
void Station::print(ostream &outfile)
{
	string accessiblity_opts;
	if (access == true)
		accessiblity_opts = "A";
	else
		accessiblity_opts = "U";

    outfile << name << " " << accessiblity_opts << " ";
}


