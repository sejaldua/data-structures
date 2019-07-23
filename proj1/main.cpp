/*
 * main.cpp – driver
 * Sejal Dua
 * Comp 15 Fall 2018 
 * 31/October/2018
 * Project 1: The Biologist's Grep
 */

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>	/* time */
#include <fstream>

#include "Trie.h"



using namespace std;


int main(int argc, char *argv[])
{

	Trie trie;

    ifstream infile;
    ofstream outfile;

	if (argc < 3) {
		cerr << "not enough inputs to run" << endl;
		return -1;
	}

  
    infile.open(argv[1]);
    outfile.open(argv[2]);

    if (!infile.is_open())
    {
        cerr << "Could not process from file\n";
        return -1;
    }

    if (!outfile.is_open())
    {
        cerr << "Failed to open file for writing\n";
        return -1;
    }

    string sequence_info = "";
    while (getline(infile, sequence_info)) {
        string request = sequence_info.substr(0, 1);
        string sequence = sequence_info.substr(2);
        if (request == "i")
        	trie.insert(sequence);
        else if (request == "q")
        	trie.query(outfile, sequence);
        else if (request == "r")
        	trie.remove(outfile, sequence);
        else
        	cout << "i don't know what to do" << endl;
    }
    
    infile.close();
    outfile.close();
}
