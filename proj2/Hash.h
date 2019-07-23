/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp
 *
 * Filename: Hash.h
 * Contains: Interface of the Hash class 
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 */


#include "Entry.h"
#include <iostream>
#include <vector>

using namespace std;

class Hash {

public:

	Hash();

	// public functions called by Gerp.cpp
	void insert(string insert_word, string word, int p_index, int line_num);
	void print_hash() const;
	Entry search(Entry query_entry) const;

private:

	// ESSENTIAL FUNCTION FOR HASH IMPLEMENTATION
	int hash_function(string word) const;

	// internal functions for expand
	bool check_load_factor() const;
	void expand();
	void transfer(Entry e);

	// helpful lowercase conversion function
	string to_lowercase(string word) const;

	// private member variables
	vector<vector<Entry> > hash_vec;
	int numElem;
	int size;

};