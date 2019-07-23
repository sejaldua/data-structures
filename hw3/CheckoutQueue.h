/*
 * CheckoutQueue.h
 * Sejal Dua
 * 1/October/2018
 * COMP15 HW3
 * Fall 2018
 *
 * Interface of the CheckoutQueue class
 *
 */

#ifndef CHECKOUTQUEUE_H
#define CHECKOUTQUEUE_H

#include "shopper.h"

class CheckoutQueue
{
public:
	CheckoutQueue();
	CheckoutQueue(int givenCapacity); 
	~CheckoutQueue();
	bool isEmpty();
	int size();
	int totalItems();
	void enqueue(Shopper);
	Shopper &front();
	void dequeue();
private:
	
	static const int INIT_CAPACITY = 2;

	Shopper *queue;

	int curr_size;
	int capacity;
	int first;
	int back;

	void expand();

};

#endif