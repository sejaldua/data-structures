/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp
 *
 * Filename: Hash.cpp
 * Contains: Implementation of the Hash class 
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 */


#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "Entry.h"
#include "Hash.h"

using namespace std;


// CONSTANTS
const double LOADFACTOR = 0.75;
const int INIT = 100000;


// Function: Hash
// Inputs: none
// Returns: none
// Does: default constructor
Hash::Hash()
{
	numElem = 0;
	hash_vec.resize(INIT);
	size = hash_vec.size();
}

// Function: insert
// Inputs: string insert word, string word, int path index, int line num
// Returns: none
// Does: checks load factor of hash data structure (if 0.75 is exceeded, 
// expand function is invoked), gets index that the insert word maps to, goes
// to that index and checks for multiplicity (checks if the lowercase
// word already exists in the struct) --> EITHER adds new occurrence
// information to existing Entry object OR pushes back a brand new entry into
// the subvector at mapped index because we are inserting a unique word
void Hash::insert(string insert_word, string word, int p_index, int line_num)
{
	// NOTE TO GRADER: uncomment next 2 lines of code for even faster runtime

	//check load factor to see if we have to expand
	if (check_load_factor())
		expand();

	// map hash word to an index value via hash function
	int index = hash_function(insert_word);

	// check if we have multiplicity -- if so, add to pre-existing Entry obj.
	int bucket_size = hash_vec[index].size();
	for (int i = 0; i < bucket_size; i++) {
		string stored_word = (hash_vec[index][i]).get_word();
		if (insert_word == stored_word) {
			hash_vec[index][i].insert_info(word, p_index, line_num);
			return;
		}
	}

	// make an Entry obj., input information, and push back into hash_vec
	Entry key(insert_word);
	key.insert_info(word, p_index, line_num);
	hash_vec[index].push_back(key);
	numElem++;
}

// Function: hash_function
// Inputs: string word
// Returns: int value
// Does: takes a string word called a key and uses the c++ functional library
// to map it to an integer value called a hashVal. This value is then modded
// by the size of the hash vectory to get our corresponding index
int Hash::hash_function(string word) const
{
	std::hash<string> hash_obj;
	size_t hashVal = hash_obj(word);
	int index = hashVal % size;
	return index;
}

// Function: check_load_factor
// Inputs: none
// Returns: bool value
// Does: returns true if the number of elements divided by the size of the
// hash_Vec is greater than the defined load factor value (0.75), prompting
// the expand function to be invoked due to a shortage of remaining capacity
bool Hash::check_load_factor() const
{
	return (((float)numElem / size) > LOADFACTOR);
}

// Function: expand
// Inputs: none
// Returns: none
// Does: allocates new memory for our hash_vec and transfers objects from
// old hash_vec (temp) to this new hash_vec so that the data structure
// is no longer approaching the load factor value
void Hash::expand()
{
	// make a new vector and assign old vector into new
	vector<vector<Entry> > new_hash;
	new_hash = hash_vec;

	// clear and resize old hash vector, making room for twice the capacity
	hash_vec.clear();
	hash_vec.resize(size * 2);

	// reset private member variables
	size = hash_vec.size();
	numElem = 0;

	// transfer contents of old vector into new vector via transfer function
	for (unsigned i = 0; i < new_hash.size(); i++) {
		for (unsigned j = 0; j < new_hash[i].size(); j++) {
			transfer(new_hash[i][j]);
		}
	}

	// releases memory 
	new_hash.clear();
}

// Function: transfer
// Inputs: Entry object e
// Returns: none
// Does: re-hashes a given Entry object into the hash vector
void Hash::transfer(Entry e)
{
	// obtains a hash index for the passed in Entry object's word variable
	string insert_word = e.get_word();
	int index = hash_function(insert_word);

	// inserts the Entry object into the subvector at index
	hash_vec[index].push_back(e);
	numElem++;
}

// Function: print_hash
// Inputs: none
// Returns: none
// Does: (*** FOR TESTING PURPOSES ***) couts the contents of the hash table
// with information about each occurrence of a non-unique word
void Hash::print_hash() const
{
    cout << "\n--------------HASH TABLE---------------\n";
    cout << "NUMELEM = " << numElem << endl;
    cout << "SIZE = " << size << endl;

    // loop through 2D vector of vectors
    for (unsigned long i = 0; i < hash_vec.size(); i++) {
    	for (unsigned long j = 0; j < hash_vec[i].size(); j++) {
			Entry e = hash_vec[i][j];

			// get vectors of occurrence info in Entry object
			vector<string> v1 = e.get_cases();
			vector<int> v2 = e.get_path_indices();
			vector<int> v3 = e.get_line_nums();

			// iterate through vectors, outputing contents to cout
			for (unsigned i = 0; i < v1.size(); i++) {
				cout << v1[i] << " --- " << v2[i] << " ";
				cout << v3[i] << endl;
			}
    	}
    }
}

// Function: search
// Inputs: Entry object query_entry
// Outputs: Entry object
// Does: extracts the query string from the passed in Entry object and if
// there are instances of this string in the hash structure, the function 
// returns the corresponding Entry object, otherwise returns the input
// Entry object as output-- queried object could not be found :(
Entry Hash::search(Entry query_entry) const
{
	// extract string from query entry and convert to lowercase
	string word = query_entry.get_word();
	string query_word = to_lowercase(word);

	// map query word to an index value via hash function
	int index = hash_function(query_word);

	// iterate through subvector / bucket at given index spot in the hash_vec
	int bucket_size = hash_vec[index].size();
	for (int i = 0; i < bucket_size; i++) {
		Entry e = hash_vec[index][i];
		string stored_word = e.get_word();

		// returns "found Entry object" if entry word matches query word
		if (query_word == stored_word) {
			return e;
		}
	}	

	// return input if hash structure does not contain lowercase query word
	return query_entry;
}

string Hash::to_lowercase(string word) const
{
	string lower;
	for (unsigned int i = 0; i < word.length(); i++)
		lower += tolower(word[i]);
	return lower;
}
