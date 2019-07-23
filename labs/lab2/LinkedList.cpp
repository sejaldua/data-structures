/*
 * LinkedList.cpp
 * COMP15
 * Fall 2018
 * 
 * Implementation for Linked List of Planets
 *
 * What is an astronaut's favorite candy bar?
 *
 * A mars bar!
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length = 0;
    head = NULL;
    curr_pos = NULL;
}

// destructor
LinkedList::~LinkedList()
{
    // point temp pointer to the head
    NodeType *temp = head;

    // traverse linked list with temp, "deleting" nodes from head to tail
    while (temp != NULL) {
        NodeType *ptr = temp;
        temp = temp->next;
        delete ptr;
    }
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l)
{
    length = l.length;
    curr_pos = NULL;
    if (l.head == NULL)
        head = NULL;
    else
    {
        head = new NodeType;
        head->info = l.head->info;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL)
        {
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function insert_planet
// Input: Planet object
// Returns: None
// Does: Adds Planet to beginning of array, increases length
void LinkedList::insert_planet(Planet p)
{
    NodeType *node = new NodeType;
    node->info = p;
    node->next = head;

    head = node;
    length++;
}


// Function insert_planet_at_back
// Input: Planet object
// Returns: None
// Does: Adds Planet to end of array, increases length
void LinkedList::insert_planet_at_back(Planet p)
{
    // instantiate new node to be appended to the back of the linked list
    NodeType *node = new NodeType;
    node->info = p;
    node->next = NULL;

    // case: linked list is empty
    if (head == NULL) {
        head = node;
        length++;
    }

    // case: linked list has node(s) in it
    else {
        NodeType *temp;
        temp = head;

        // traverse linked list with until temp points to NULL
        while (temp->next != NULL) {
            temp = temp->next;
        }

        // point temp to the new node and increment the length
        temp->next = node;
        length++;
    }

}

// Function get_next_planet
// Inputs: none
// Returns: none
// Does: Returns the Planet object at the current pos
//       Wraps around to beginning if we're at the end
//       Returns a default planet if empty
Planet LinkedList::get_next_planet()
{
    if (length == 0)
    {
        Planet p;
        return p;
    }
    if (curr_pos == NULL)
        curr_pos = head;
    else
        curr_pos = curr_pos->next;
    return curr_pos->info;
}

// Function get_length, const
// Inputs: none
// Returns: int, length of list
int LinkedList::get_length() const
{
    return length;
}

// Function print, const
// Inputs: ostream object
// Returns: none
// Does: prints every element in the list
void LinkedList::print(ostream &out) const
{
    NodeType *node = head;
    while (node != NULL)
    {
        (node->info).print(out);
        out << endl;
        node = node->next;
    }
}