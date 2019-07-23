/*
 * LinkedList.cpp
 * Sejal Dua
 * 24/September/2018
 * COMP15 HW2
 * Fall 2018
 * 
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length = 0;
    head = NULL;
    curr_pos = NULL;
}

// Destructor
LinkedList::~LinkedList() 
{
    // point temp pointer to the head
    NodeType *temp = head;

    // traverse linked list with temp, "deleting" nodes from first to last
    while (temp != NULL) {
        NodeType *ptr = temp;
        temp = temp->next;
        delete ptr;
        length--;
    }
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l)
{
    NodeType *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    curr_pos = NULL;
    if (l.head == NULL)
        head = NULL;
    else
    {
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL)
        {
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function: get_length
// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::get_length() const
{
    return length;
}

// Function: insert_station
// Input: Station object
// Returns: none
// Does: inserts the station into the head of the list
void LinkedList::insert_station(Station s)
{
    // instantiate a new node, fill it with Station s, and set its next to head
    NodeType *node = new NodeType;
    node->info = s;
    node->next = head;

    // reassign head with the node and increment the length of the linked list
    head = node;
    length++;
}

// Function: remove_station
// Input: Station object
// Returns: none
// Does: "deletes" and deallocates memory for the first instance of
// the station which contains identical information as the passed in
// station object
void LinkedList::remove_station(Station s)
{
    // point both current and prev to the head to begin
    NodeType *current = head;
    NodeType *prev = current;

    // traverse LL until we find the station to remove or arrive at end of LL
    while (!(current->info.is_equal(s))) {
        if (current == NULL)
            break;
        else {
            prev = current;
            current = current->next;
        }
    }

    // check to see if curr_pos is pointing to the station we wish to remove
    if (curr_pos == current)
        reset_curr_pos();

    // the case for when we wish to remove the first node of the linked list
    if (current == head) 
        head = current->next;

    // the case for when we wish to remove any other node (not the head)
    else 
        prev->next = current->next;

    // remove the station and decrement the length of the linked list
    delete current;
    length--;
}


// Function: get_next_station
// Input: none
// Returns: Planet object
// Does: returns the Station object at the current position, wraps around
// to the beginning if we're at the end, or returns a default station if empty
Station LinkedList::get_next_station()
{
    // if there are no nodes in the array, instantiate a station and return it
    if (length == 0) {
        Station s;
        return s;
    }

    // if curr_pos points to null, set it to head, the first element in the LL
    if (curr_pos == NULL)
        curr_pos = head;

    
    // assign a temp to curr_pos and bump curr_pos to next element in LL
    NodeType *temp = curr_pos;
    curr_pos = curr_pos->next;
    
    // return the info that the node at temp stores (Station object)
    return temp->info;

    
}

// Function: reset_list
// Input: none
// Returns: none
// Does: sets the variable curr_pos to null
void LinkedList::reset_curr_pos()
{
   curr_pos = NULL;
}

// Function: make_empty
// Input: none
// Returns: none
// Does: "deletes" all elements in the list and deallocates any memory
void LinkedList::make_empty()
{
    // point temp pointer to the head
    NodeType *temp = head;

    // traverse linked list with temp, "deleting" nodes from first to last
    while (temp != NULL) {
        NodeType *ptr = temp;
        temp = temp->next;
        delete ptr;
        length--;
    }
}



// Function: print
// Input: ostream address
// Returns: none
// Does: prints all stations into the given ostream, outputs distance
// to the final stop, and prints tracks (==) between stations
void LinkedList::print(ostream &out)
{

    // since all stations are to be printed, start fresh by resetting curr_pos
    reset_curr_pos();

    // loop through length of LL, accessing each station via get_next_station
    int i = 1;
    while (i <= get_length()) {
        Station s = get_next_station();
        s.print(out);
        if (i != get_length()) 
            out << get_length() - i << " == ";
        else
            out << get_length() - i << endl;
        i++;
    }

}



