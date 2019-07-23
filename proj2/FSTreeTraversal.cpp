/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 28/November/2018
 * Project 2: Gerp [PHASE 1]
 *
 * Filename: FSTreeTraversal.cpp
 * Contains: Driver for Project 2
 * Part of: Project 2 "Gerp" Phase 1 for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "DirNode.h"
#include "FSTree.h"

using namespace std;

void list_all(DirNode *node, string directory);

int main(int argc, char *argv[])
{
	// throws error if incorrect number of command line arguments
	if (argc != 2) 
	{
		cerr << "usage: " << argv[0] << " directory" << endl;
		return -1;
	}

	string directory = argv[1];
	FSTree file_tree(directory);
	DirNode *root = file_tree.getRoot();
	list_all(root, directory);

}

// Function: list_all
// Inputs: DirNode node, directory string
// Returns: none
// Does: traverses the file system from the given directory and lists all 
// subdirectories and files within it
void list_all(DirNode *node, string directory)
{

	// checks within the given directory if there are files to traverse thru
	if (node->isEmpty()) {
		cout << directory << endl;
		return;
	}

	// saves int vars for file count and subdirectory count
	int num_files = node->numFiles();
	int num_subdirs = node->numSubDirs();

	// iterates through files within given directory and prints them to cout
	for (int i = 0; i < num_files; i++)
		cout << directory + "/" + (node->getFile(i)) << endl;

	// iterates through subdirectories and calls function recursively on them
	for (int i = 0; i < num_subdirs; i++) {
		DirNode *temp = node->getSubDir(i);
		string subdir = directory + "/" + (temp->getName());
		list_all(temp, subdir);
	}

	cout << directory << endl;

}