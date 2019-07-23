/*
 * LinkedList.h
 * Sejal Dua
 * 24/September/2018
 * COMP15 HW2
 * Fall 2018
 *
 * Interface for Linked List of Green Line Extension Stations
 *
 */

#include "Station.h"
#include <fstream>

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

class LinkedList
{
public:
    LinkedList();                                   // Default constructor
    ~LinkedList();                                  // Default constructor
    LinkedList & operator = (const LinkedList &);   // Assignment Operator
    LinkedList(const LinkedList &);                 // copy constructor. 
                                                    // Creates a new list, 
                                                    // identical to given one


    void insert_station(Station);              // Inserts a station into list
    void remove_station(Station);              // Removes a station fromlist
    void make_empty();                         // Empties the list
    void reset_curr_pos();                     // Sets curr-pos to NULL
    Station get_next_station();                // Gives a new station

    
    int get_length() const;                    // Returns the length of the list
    void print(ostream &);                     // Print the list of stations 


private:
    int length;
    NodeType *head;
    NodeType *curr_pos;
};

#endif
