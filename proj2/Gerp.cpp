/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp
 *
 * Filename: Gerp.cpp
 * Contains: Implementation of the Gerp class 
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 */


#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "FSTree.h"
#include "Entry.h"
#include "Gerp.h"

using namespace std;

const int INIT = 500;

// Function: Gerp
// Inputs: none
// Returns: none
// Does: default constructor
Gerp::Gerp()
{
	paths.reserve(INIT);
	p_index_ctr = 0;
}

// Function: populate_hash
// Inputs: string directory (file path)
// Returns: none
// Does: builds an FSTree, gets the root, and recursively populates the 
// hash table starting from root node with the filepath of the root directory
void Gerp::populate_hash(string directory)
{
	FSTree file_tree(directory);
	DirNode *root = file_tree.getRoot();
	populate_hash(root, directory);

	//NOTE: uncomment line below to view contents of the hash after populating
	//h.print_hash();
}

// Function: populate_hash
// Inputs: DirNode node pointer, directory string
// Returns: none
// Does: recursively traverses the file system from the given directory and 
// parses all files within all subdirectories in order to fully populate
// the hash data structure
void Gerp::populate_hash(DirNode *node, string curr_filepath)
{
	// checks within the given directory if there are files to traverse thru
	if (node->isEmpty())
		return;

	// saves int vars for file count and subdirectory count
	int num_files = node->numFiles();
	int num_subdirs = node->numSubDirs();

	// iterates through files within given directory and parses them
	for (int i = 0; i < num_files; i++)
		parse_file(curr_filepath + "/" + (node->getFile(i)));

	// iterates through subdirectories and calls function recursively on them
	for (int i = 0; i < num_subdirs; i++) {
		DirNode *temp = node->getSubDir(i);
		string subdir = curr_filepath + "/" + (temp->getName());
		populate_hash(temp, subdir);
	}
}

// Function: parse_file
// Inputs: string filepath
// Returns: none
// Does: parses each word in the file and hashes it as efficiently as possible.
// That is, when parsing a line from the file, if a duplicate of a word is
// encountered, only one instance of that word is hashed. If a string is
// composed of all non-alphanumeric characters, an empty string is not hashed
// because such a string would never be queried. Finally, we hash the 
// lowercase version of words and then store the case sensitive variation
// in a vector within the Entry object in wish the lowercase word is hashed.
// As far as paths, we just store path vector index in a vector of path
// vector indices within the Entry object. Regarding lines, we just store 
// the line number because storing the full line would consume too much space.
void Gerp::parse_file(string filepath)
{
	// instantiate vars
	ifstream infile;
	infile.open(filepath.c_str());
	int line_num_ctr = 1; 
	string line, word;
	vector<string> line_strs;
	line_strs.reserve(100);

	// process file line by line
	while(getline(infile, line)) {

		// process line word by word using cin >> operator
		stringstream ss(line);
		while (ss >> word) {
			word = strip_string(word);
			if (need_to_insert(word, line_strs)) {
				line_strs.push_back(word);
				string lower = to_lowercase(word);
				h.insert(lower, word, p_index_ctr, line_num_ctr);
			}
		}
		line_num_ctr++;
		line_strs.clear();
	}
	paths.push_back(filepath);
	p_index_ctr++;
	infile.close();
}

// Function: need_to_insert
// Inputs: string word, vector<string> line_strs (passed in by ref)
// Outputs: bool
// Does: checks if the passed in word is empty or a duplicate within the 
// file line and returns false if either of those conditions are true, 
// otherwise returns true
bool Gerp::need_to_insert(string &word, vector<string> &line_strs) const
{
	// check if the string is empty b/c no need to make a hash of ""
	if (word.empty())
		return false;

	// iterates through vector of previously inserted strings
	for (unsigned long i = 0; i < line_strs.size(); i++)
	{

		// if word is a duplicate
		if (word == line_strs[i])
			return false;
	}

	// if we make it here, we need to insert the word into the hash table
	return true;
}

// Function: to_lowercase
// Inputs: string word
// Returns: string
// Does: iterates through the chars of the given string, invoking the 
// tolower(str) function on each char in the string and concatenating the
// lowercase char to a new string being built up; returns the lowercase string
string Gerp::to_lowercase(string word) const
{
	string lower;
	for (unsigned int i = 0; i < word.length(); i++)
		lower += tolower(word[i]);
	return lower;
}

// Function: strip_string
// Inputs: string str
// Returns: string
// Does: strips all leading and trailing non-alphanumeric characters 
// from the query and returns string to print to cout
string Gerp::strip_string(string str) const
{
	// strip leading non-alphanumeric characters
	while (!str.empty() && !isalnum(str[0]))
		str = str.substr(1);

	// strip trailing non-alphanumeric characters
	while (!str.empty() && !isalnum(str[str.length() - 1]))
		str = str.substr(0, str.length()-1);

	return str;
}

// Function: query_s (case sensitive)
// Inputs: string q_str (stripped query string)
// Returns: none
// Does: since Entry objects contain the bare minimum amount of information
// we need for our post-query cout statements, we must obtain an Entry object
// from our hash search and then interpret the contents of this Entry object.
// We either get the very same Entry object that we passed into the search
// function, in which case we check to see if the vectors all have size 0
// (which is true for the query Entry object we initially made), or we
// iterate through the length of the occurrences of the word (of varying cases)
// and print out the file source information of each of the variations
// which match the exact case of the queried string.
void Gerp::query_s(string q_str)
{
	// makes a basic Entry object from the query string and searches it in hash
	Entry query_entry(q_str);
	Entry found_entry = h.search(query_entry);

	// determine if the obtained Entry object came from the hash or was my arg
	int occurrences = found_entry.get_index();
	if (occurrences == -1)
		cout << q_str << " Not Found. Try with @insensitive or @i." << endl;
	else {

		// iterate through occurrences of the str, cout the (CS) matching ones
		bool found_one = false;
		for (int i = 0; i <= occurrences; i++) {
			if (found_entry.get_case_sensitive(i) == q_str) {
				string fp = paths[found_entry.get_path_index(i)];
				int ln = found_entry.get_line_num(i);
				cout << fp << ":" << ln << ": " << file_line(fp, ln) << endl;
				found_one = true;
			}
		}

		// cout "not found" statement if none match query str identically
		if (!found_one)
			cout << q_str << " Not Found. Try with @insensitive or @i."<< endl;
	}
}

// Function: query_i (case insensitive)
// Inputs: string q_str (stripped query string)
// Returns: none
// Does: The same design is mimicked in this case insensitive query function,
// with the exception that before we search our hash data structure, we 
// convert the stripped query string to lowercase because we do not care if
// we are querying for HeLLo, we just want all occurrences stored in the 
// "hello" Entry object (recall: Entry objects are hashed by LOWERCASE words).
// Once we obtain our number of occurrences of the query string, we iterate
// through the vectors storing occurrence information and cout the source info.
void Gerp::query_i(string q_str)
{
	// convert query string to lower case
	string lowered_str = to_lowercase(q_str);

	// makes a basic Entry object from the query string and searches it in hash
	Entry query_entry(lowered_str);
	Entry found_entry = h.search(query_entry);

	// determine if the obtained Entry object came from the hash or was my arg
	int occurrences = found_entry.get_index();
	if (occurrences == -1)
		cout << q_str << " Not Found." << endl;

	else {

		// cout the source info corresponding to each occurrence of @i q_str
		for (int i = 0; i <= occurrences; i++) {
			string fp = paths[found_entry.get_path_index(i)];
			int ln = found_entry.get_line_num(i);
			cout << fp << ":" << ln << ": " << file_line(fp, ln) << endl;
		}
	}
}

// Function: file_line
// Inputs: string filepath, int line_num
// Returns: string
// Does: returns the desired line as it appears in the source file by opening
// an ifstream object given the filepath and calling the getline function x
// number of times, where x = line_num
string Gerp::file_line(string filepath, int line_num) const
{
	ifstream infile;
	infile.open(filepath.c_str());
	string line;
	for (int i = 0; i < line_num; i++) {
		getline(infile, line);
	}
	infile.close();
	return line;
}
