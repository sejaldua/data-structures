/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp
 *
 * Filename: Entry.cpp
 * Contains: Implementation of the Entry class 
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 *
 */


#include <iostream>
#include "Entry.h"

using namespace std;

const int INIT = 500;

// Function: default constructor
// Inputs: none
// Returns: none
// Does: instantiates an Entry object with a default name
Entry::Entry() 
{
	word = "WORD";
	cases.reserve(INIT);
	path_indices.reserve(INIT);
	line_nums.reserve(INIT);
	index = -1;
}


// Function: parameterized constructor
// Inputs: string word_hash
// Returns: none
// Does: assigns arguments to private member variables of the Entry class
Entry::Entry(string word_hash) 
{
	word = word_hash;
	cases.reserve(INIT);
	path_indices.reserve(INIT);
	line_nums.reserve(INIT);
	index = -1;
}

// Function: get_word
// Inputs: none
// Returns: string
// Does: getter for Entry word
string Entry::get_word() const
{
	return word;
}

// Function: get_case_sensitive
// Inputs: int index
// Returns: string
// Does: getter for case sensitive variation of occurrence
string Entry::get_case_sensitive(int ind) const
{
	return cases[ind];
}

// Function: get_path_index
// Inputs: int index
// Returns: int
// Does: getter for path index of occurrence
int Entry::get_path_index(int ind) const
{
	return path_indices[ind];
}

// Function: get_line_num
// Inputs: int index
// Returns: int
// Does: getter for line number of occurrence
int Entry::get_line_num(int ind) const
{
	return line_nums[ind];
}

// Function: get_index
// Inputs: none
// Returns: int
// Does: getter for index (indicates size of occurrence vectors in Entry obj)
int Entry::get_index() const
{
	return index;
}

// Function: get_cases
// Inputs: none
// Returns: vector of strings
// Does: getter for cases vector
vector<string> Entry::get_cases() const
{
	return cases;
}

// Function: get_path_indices
// Inputs: none
// Returns: vector of ints
// Does: getter for path_indices vector
vector<int> Entry::get_path_indices() const
{
	return path_indices;
}

// Function: get_line_nums
// Inputs: none
// Returns: vector of ints
// Does: getter for line_nums vector
vector<int> Entry::get_line_nums() const
{
	return line_nums;
}

// Function: insert_info
// Inputs: string case_insensitive, int p_index, int line_num
// Returns: none
// Does: pushes back arguments into private vectors of occurrence info
void Entry::insert_info(string case_sensitive, int p_index, int line_num)
{
	cases.push_back(case_sensitive);
	path_indices.push_back(p_index);
	line_nums.push_back(line_num);
	index++;
}

// Function: merge
// Inputs: Entry object e
// Returns: none
// Does: extracts information from the first spot in passed in Entry object's
// vectors and pushes back info into current/this Entry object's vectors
// of occurrence information (NOTE: no longer using this function)
void Entry::merge(Entry e)
{
	cerr << "merging" << endl;
	cases.push_back(e.get_case_sensitive(0));
	path_indices.push_back(e.get_path_index(0));
	line_nums.push_back(e.get_line_num(0));
	index++;
}


