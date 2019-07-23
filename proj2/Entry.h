/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp
 *
 * Filename: Entry.h
 * Contains: Interface of the Entry class 
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 */


#ifndef ENTRY_H_
#define ENTRY_H_

#include <ostream>
#include <vector>

using namespace std;

class Entry {

public:

	// constructors
	Entry();
	Entry(string word_hash);

	// getters
	string get_word() const;
	string get_case_sensitive(int index) const;
	int get_path_index(int index) const;
	int get_line_num(int index) const;
	int get_index() const;
	vector<string> get_cases() const;
	vector<int> get_path_indices() const;
	vector<int> get_line_nums() const;

	// helpful functions
	void insert_info(string case_sensitive, int p_index, int line_num);
	void merge(Entry e);

private:
	string word;
	vector<string> cases;
	vector<int> path_indices;
	vector<int> line_nums;
	int index;

};

#endif