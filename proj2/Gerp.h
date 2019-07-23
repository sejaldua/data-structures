/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 5/December/2018
 * Project 2: Gerp [PHASE 2]
 *
 * Filename: Gerp.h
 * Contains: Interface of the Gerp class
 * Part of: Project 2 "Gerp" Phase 2 for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <vector>

#include "DirNode.h"
#include "Hash.h"

#ifndef GERP_H_
#define GERP_H_

using namespace std;


class Gerp
{
public:
	Gerp();
	void populate_hash(string directory);
	string strip_string(string str) const;
	void query_i(string q_str);
	void query_s(string q_str);

private:
	void populate_hash(DirNode *node, string curr_filepath);
	void parse_file(string filepath);
	bool need_to_insert(string &word, vector<string> &line_strs) const;
	string to_lowercase(string word) const;
	string file_line(string filepath, int line_num) const;

	Hash h;
	vector<string> paths;
	int p_index_ctr;
};

#endif