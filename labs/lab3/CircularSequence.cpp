/*
 *      CircularSequence.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 */

#include <iostream>
#include <stdexcept>

#include "CircularSequence.h"


using namespace std;


/*
 * Return the index of the next element in the sequence.
 * Wraps around!
 */
int CircularSequence::nextIndex(int index)
{
    return (index + 1) % capacity;

}


/* Default Constructor */
CircularSequence::CircularSequence()
{
        init(INIT_CAPACITY);
}

/* 
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity. 
 */
CircularSequence::CircularSequence(int initialCapacity)
{
        init(initialCapacity);
}

/*
 * Initialize a new, empty sequence with an initial capacity.
 */
void CircularSequence::init(int initialCapacity)
{
        capacity      = initialCapacity;
        sequenceArray = new ElementType[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularSequence::~CircularSequence()
{
        delete [] sequenceArray;
}

/* 
 *  Add given element to the back of the list (at element
 *  currentSize). 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtBack(ElementType elem) 
{
        if (currentSize == capacity) {
                expand();
        }
        sequenceArray[back] = elem;
        back                = nextIndex(back);
        currentSize++;
        if (back == capacity) {
            back = 0;
        }
        return true;
}

/* 
 *  Add given element to the front of the list (at element 0)
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtFront(ElementType elem)
{

    // check if there is any more room in the list
    if (currentSize == capacity) {
        expand();
    }

    // insert element to the front of the list
    sequenceArray[front] = elem;

    // wrap front to the back and increment currentSize
    front = back + 1;
    currentSize++;

    return true;
}
                
/*
 * Remove the element at the back of the list (index currentSize - 1)
 * and return it.
 */
ElementType CircularSequence::removeFromBack() 
{
    ElementType temp = sequenceArray[back];
    back = back - 1;
    currentSize--;
    return temp;
}
 
/*
 * Remove the element at the front of the list (element 0)
 * and return it.
 */
ElementType CircularSequence::removeFromFront()
{
     ElementType temp = sequenceArray[front];
     front = nextIndex(front);
     currentSize--;
     return temp;
}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularSequence::expand() 
{
    capacity = capacity * 2;
    ElementType *bigSeqArray = new ElementType[capacity];
    
    int i = 0;
    while (i < currentSize) {
        bigSeqArray[i] = sequenceArray[i];
        i++;
    }

    delete[] sequenceArray;
    sequenceArray = bigSeqArray;
}
    
/*
 * Print the contents of the sequence, one element per line.
 */
void CircularSequence::printSequence() 
{
        int currIndex = front;
        for (int i = 0; i < currentSize; i++) {
                cout << sequenceArray[currIndex] << endl;
                currIndex = nextIndex(currIndex);
        }
}
