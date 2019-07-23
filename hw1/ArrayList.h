/*
 * ArrayList.h
 * Sejal Dua
 * 17/September/2018
 * COMP 15 HW1
 * Fall 2018
 *
 * Interface for Array of Pirates, matey
 */

#include "Pirate.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef ARRAY_H_
#define ARRAY_H_

const int MAX_PIRATES = 100;

class ArrayList
{
public:
    // Default constructor
    ArrayList();
    ~ArrayList();

    // The basic operations:
    // Find, Insert, Delete, and Get Next
    Pirate find_pirate(Pirate, bool &) const;
    void insert_pirate(Pirate);
    void delete_pirate(Pirate);
    Pirate get_next_pirate();

    // Start over at the beginning of the list
    void make_empty();
    void reset_array();

    // Return some basic info
    bool is_full() const;
    int get_length() const;

    // Print the array
    void print(ostream&) const;

private:
    int length;
    int capacity;
    int curr_pos;
    Pirate *pirates;

    // Expand and shrink functions to adjust size of array
    void expand();
    void shrink();
};

#endif
