/*
 * Sejal Dua
 * 1/October/2018
 * CheckoutQueue.cpp
 * COMP15 HW3
 * Fall 2018
 *
 * Implementation of the CheckoutQueue class. Contains a constructor and 
 * destructor, public isEmpty, size, totalItems, enqueue, dequeue, and
 * front functions. The front function, especially, is important for
 * abstraction purposes. As far as private functions, it comtains an
 * expand function, which follows the same pseudocode as that which
 * we worked on in HW1 ArrayList.cpp.
 */

#include <iostream>
#include "CheckoutQueue.h"

using namespace std;

// Function: CheckoutQueue constructor
// Input: none
// Returns: none
// Does: initializes an empty queue
CheckoutQueue::CheckoutQueue()
{
	capacity = INIT_CAPACITY;
    queue = new Shopper[capacity];
    curr_size = 0;
    first = 0;
    back = 0;
}

// Function: CheckoutQueue destructor
// Input: none
// Returns: none
// Does: deletes whole structure and deallocates memory
CheckoutQueue::~CheckoutQueue()
{
	delete[] queue;
}

// Function: isEmpty
// Input: none
// Returns: bool value
// Does: returns true iff this instance of CheckoutQueue class is empty
bool CheckoutQueue::isEmpty()
{
	return curr_size == 0;
}

// Function: size
// Input: none
// Returns: integer
// Does: returns the number of shoppers in the queue
int CheckoutQueue::size()
{
	return curr_size;
}


// Function: totalItems
// Input: none
// Returns: integer
// Does: sum of the items_left field of every shopper in the queue
int CheckoutQueue::totalItems()
{
	int sum = 0;
	for (int i = 0; i < curr_size; i++) {
		sum += queue[i].items_left;
	}
	return sum;
}

// Function: enqueue
// Input: Shopper object
// Returns: none
// Does: puts shopper at at the end of the queue
void CheckoutQueue::enqueue(Shopper toAdd)	
{
	if (curr_size > capacity) 
		expand();
	queue[back] = toAdd;
	back++;
	curr_size++;
}

// Function: front
// Input: none
// Returns: Shopper object
// Does: reference to the front element (Shopper) in the queue, throws
// a C++ runtime_error with the message empty_queue
Shopper &CheckoutQueue::front()
{
	if (isEmpty()) {
		throw runtime_error("empty_queue");
	}
	else
		return queue[first];
}

// Function: dequeue
// Input: none
// Returns: none
// Does: removes the element at the front of the queue
void CheckoutQueue::dequeue()
{
	if (isEmpty()) 
		throw runtime_error("empty_queue");
	else {
		first = (first + 1) % capacity;
		curr_size--;
	}
}

// PRIVATE FUNCTIONS

// Function: expand
// Input: none
// Return: none
// Does: Expands / doubles the capacity of the array and reallocates
// data into a new array with twice as much space.
void CheckoutQueue::expand()
{
	// adjusts capacity, instantiates new dynamic array
    capacity = capacity * 2;
    Shopper *bigger = new Shopper[capacity];

    // reallocates elements to new array
    int i = 0;
    while (i < curr_size) {
        bigger[i] = queue[i];
        i++;
    }

    // "deletes" initial array to free up memory and updates pointer
    delete[] queue;
    queue = bigger;



}


