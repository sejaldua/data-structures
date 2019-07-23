/*
 * ArrayList.h
 * Sejal Dua
 * 31/October/2018
 * COMP 15 Proj1
 * Fall 2018
 *
 * Interface for Array of Trie sequences
 */

#include <iostream>
#include <string>
using namespace std;

#ifndef ARRAY_H_
#define ARRAY_H_

class ArrayList
{
public:
    // Default constructor
    ArrayList();
    ~ArrayList();

    // Parameterized constructor
    ArrayList(int num_seqs);

    // insert sequence
    void insert_seq(string seq);

    string find_max() const;
    string find_min() const;

    int get_length() const;

    // Print the array
    void print(ostream&) const;

private:
    int length;
    int capacity;
    string *strings;

    void expand();


};

#endif
