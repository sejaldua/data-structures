/*
 * ArrayList.cpp
 * Sejal Dua
 * 31/October/2018
 * COMP 15 Proj1
 * Fall 2018
 */

#include "ArrayList.h"


const int SEQUENCES = 100;

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList()
{
    int length = 0;
    int capacity = SEQUENCES;
    seqs = new string[capacity];
}

ArrayList::ArrayList(int num_seqs)
{
    int length = 0;
    int capacity = num_seqs;
    seqs = new string[capacity]
}

// destructor
ArrayList::~ArrayList()
{
    delete[] seqs;
}

/* 
 * Function insert_pirate
 * Inputs: Pirate object
 * Returns: Nothing
 * Does: First checks to make sure everything is unique, then checks 
 * if the array needs to be expanded, and finally inserts given Pirate
 * at the end of the list
 */
void ArrayList::insert_string(string s)
{
    // checks if the given Pirate object already exists in the dynamic array
    for (int i = 0; i < length; i++) {
        if (seqs[i] == s) 
            break;
    }       

    // checks if the capacity of the dynamic array needs to be expanded    
    if (length >= capacity) {
        expand();
    }

    // inserts the seq at the end and increments the length
    seqs[length] = s;
    length++;
}


/* 
 * Function make_empty
 * Input: none
 * Returns: none
 * Does: sets length to 0 (memory not modified)
 */
void ArrayList::make_empty()
{
    for (int i = 0; i < length; i++)
        seqs[i] = "";
    length = 0;
}

/*
 * Function print
 * Input: ostream object address of outfile
 * Returns: none
 * Does: Loops through the dynamic array of seqs and
 * calls each pirate's member print function, inserting
 * a comma and space in between each pirate's print output, 
 * with the exception of the final one in the array
 */
void ArrayList::print(ostream &outfile) const 
{
    for (int i = 0; i < length; i++){
        seqs[i].print(outfile);

        // check if at the last element in the array before inserting a comma
        if (i != length - 1)
            outfile << ", ";
    }
}

/* 
 * Function get_length
 * Input: none, oncst
 * Returns: int
 * Does: Returns the value in length attribute
 */
int ArrayList::get_length() const
{
    return length;
}

/*
 * Function expand
 * Input: none
 * Returns: none
 * Does: Expands the capacity of the array so that it can
 * accommodate any number of seqs. When the actual number
 * of seqs in the array reaches maximum capacity, elements are 
 * reallocated into a new array with twice as much space.
 */
void ArrayList::expand()
{
    // adjusts capacity, instantiates new dynamic array, and cout announcement
    capacity = capacity * 2;
    Pirate *seqsBigger = new Pirate[capacity];
    cout << "Expand to " << capacity << endl;

    // reallocates elements to new array
    int i = 0;
    while (i < length) {
        seqsBigger[i] = seqs[i];
        i++;
    }

    // "deletes" initial array to free up memory and updates pointer
    delete[] seqs;
    seqs = seqsBigger;
}

string ArrayList::find_min() const
{
    int best_index = 0;

    for (int i = 1; i <= arr_index; i++) {
        if (seqs[i] < seqs[best_index])
            best_index = i;
    }

    return seqs[best_index];
}

string ArrayList::find_max() const
{
    int best_index = 0;

    for (int i = 1; i <= arr_index; i++) {
        if (seqs[i] > seqs[best_index])
            best_index = i;
    }

    return seqs[best_index];
}
