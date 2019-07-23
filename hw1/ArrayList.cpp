/*
 * ArrayList.cpp
 * Sejal Dua
 * 17/September/2018
 * COMP 15 HW 1
 * Fall 2018
 *
 * This is the implementation for an Arrrrrrray of Pirates.
 * It dynamically allocates space in the heap and handles
 * inserts and deletions of pirates. It proactively triggers
 * capacity expansions and shrinkages when it is a logical
 * time to make an adjustment to the dynamic array.  It also
 * includes a print function which outputs pirate information 
 * to a specified ostream object.
 */

#include "ArrayList.h"

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList()
{
    length = 0;
    curr_pos = 0;
    pirates = new Pirate[MAX_PIRATES];
    capacity = MAX_PIRATES;
}

// destructor
ArrayList::~ArrayList()
{
    delete[] pirates;
}

/*
 * Function find_pirate
 * Inputs: Pirate object, bool by reference
 * Returns: Pirate object
 * Does: Looks for pirate in the array, modifies bool if found
 *       Returns the object from the list and not the passed one
 *      (In case they're different.)
 */
Pirate ArrayList::find_pirate(Pirate p, bool &found) const
{
    int location = 0;
    while ((location < length) && !found)
    {
        if (p == pirates[location])
        {
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

/* 
 * Function insert_pirate
 * Inputs: Pirate object
 * Returns: Nothing
 * Does: First checks to make sure everything is unique, then checks 
 * if the array needs to be expanded, and finally inserts given Pirate
 * at the end of the list
 */
void ArrayList::insert_pirate(Pirate p)
{
    // checks if the given Pirate object already exists in the dynamic array
    for (int i = 0; i < length; i++) {
        if (pirates[i] == p) 
            break;
    }       

    // checks if the capacity of the dynamic array needs to be expanded    
    if (length >= capacity) {
        expand();
    }

    // inserts the pirate at the end and increments the length
    pirates[length] = p;
    length++;
}

/* 
 * Function delete_pirate
 * Inputs: Pirate object
 * Returns: Nothing
 * Does: Deletes pirate, shifts everything else over, and checks 
 * to see the array needs shrinking
 */
void ArrayList::delete_pirate(Pirate p)
{
    // iterates through the array, searching for the given Pirate object
    for (int i = 0; i < length; i++) {
        if (pirates[i] == p) {

            // shifts Pirate objects to the left, thereby "deleting" Pirate p
            for (int j = i; j < length - 1; j++) {
                pirates[j] = pirates[j + 1];
            }
            length--;
        }
    }
    
    // check if the capacity of the dynamic array should be shrunk
    if (length < capacity / 2) {
        shrink();
    }

}

/* 
 * Function get_next_pirate
 * Input: None
 * Returns: Pirate object
 * Does: Returns pirate at curr_pos
 *       Increments curr_pos, but wraps around
 */
Pirate ArrayList::get_next_pirate()
{
    Pirate p = pirates[curr_pos];
    curr_pos = (curr_pos + 1) % length;
    return p;
}

/* 
 * Function make_empty
 * Input: none
 * Returns: none
 * Does: sets length to 0 (memory not modified)
 */
void ArrayList::make_empty()
{
    length = 0;
}

/* 
 * Function reset_array
 * Input: none
 * Returns: none
 * Does: sets curr_pos to 0 
 */
void ArrayList::reset_array()
{
    curr_pos = 0;
}

/*
 * Function print
 * Input: ostream object address of outfile
 * Returns: none
 * Does: Loops through the dynamic array of pirates and
 * calls each pirate's member print function, inserting
 * a comma and space in between each pirate's print output, 
 * with the exception of the final one in the array
 */
void ArrayList::print(ostream &outfile) const 
{
    for (int i = 0; i < length; i++){
        pirates[i].print(outfile);

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
 * accommodate any number of pirates. When the actual number
 * of Pirates in the array reaches maximum capacity, elements are 
 * reallocated into a new array with twice as much space.
 */
void ArrayList::expand()
{
    // adjusts capacity, instantiates new dynamic array, and cout announcement
    capacity = capacity * 2;
    Pirate *piratesBigger = new Pirate[capacity];
    cout << "Expand to " << capacity << endl;

    // reallocates elements to new array
    int i = 0;
    while (i < length) {
        piratesBigger[i] = pirates[i];
        i++;
    }

    // "deletes" initial array to free up memory and updates pointer
    delete[] pirates;
    pirates = piratesBigger;
}

/* 
 * Function shrink
 * Input: none
 * Returns: none
 * Does: Shrinks the capacity of the array. When the actual number
 * of Pirates in the array dips below half its capacity, elements
 * are reallocated into a new array with half as much spacfec.
 */
void ArrayList::shrink() 
{
    // adjusts capacity, instantiates new dynamic array, and cout announcement
    capacity = capacity / 2;
    Pirate *piratesSmaller = new Pirate[capacity];
    cout << "Contract to " << capacity << endl;

    // reallocates elements to new array
    int i = 0;
    while (i < length) {
        piratesSmaller[i] = pirates[i];
        i++;
    }

     // "deletes" initial array to free up memory and updates pointer
    delete[] pirates;
    pirates = piratesSmaller;
}
