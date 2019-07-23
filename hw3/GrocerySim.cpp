/*
 * CheckoutQueue.h
 * Sejal Dua
 * 1/October/2018
 * COMP15 HW3
 * Fall 2018
 *
 * Implementation of the CheckoutQueue class. Simulates the flow of
 * shoppers and processing transactions in a grocery store or supermarket.
 * Contains a constructor and destructor, a run function, and 3 helper
 * functions: populate_storage, print, and distribute. The run function
 * is the function that simulates all of the processes that occur in the
 * store system, and helper functions are simply used for modularity and
 * ease of understanding.
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"


using namespace std;


// Function: GrocerySim constructor
// Input: none
// Output: none
// Does: initializes a GrocerySim object
GrocerySim::GrocerySim()
{
	num_std_lanes         = 8;
	num_exp_lanes         = 3;
	num_total_lanes       = num_std_lanes + num_exp_lanes;
	max_exp_items         = 10;
	curr_time             = 0;
	total_shoppers        = 0;
	shoppers_finished     = 0;

	lanes                 = new CheckoutQueue[num_total_lanes];
}

// Function: parameterized GrocerySim constructor
// Input: number of standard checkout lanes, number of express checkout lanes
// 		  and the max number of items one can have to use the express lane
// Returns: none
// Does: initializes a GrocerySim object / data structure
GrocerySim::GrocerySim(int num_std, int num_express, int max_express)
{
	num_std_lanes = num_std;
	num_exp_lanes = num_express;
	max_exp_items = max_express;

	num_total_lanes       = num_std_lanes + num_exp_lanes;
	curr_time             = 0;
	total_shoppers        = 0;
	shoppers_finished     = 0;

	lanes = new CheckoutQueue[num_total_lanes];
}

// Function: destructor
// Input: none
// Returns: none
// Does: deletes the whole structure and liberates any allocated memory
GrocerySim::~GrocerySim()
{
	delete[] lanes;
}

// Function: run
// Input: reference to an istream address
// Returns: none
// Does: reads shopper details and executes simulation
void GrocerySim::run(istream &infile)
{
	// reads the shoppers in to a storage queue
	populate_storage(infile);

	// while there are still more shoppers to finish processing items...
	while (shoppers_finished < total_shoppers) {

		// processes one item for the first shopper of each lane (if not empty)
		for (int i = 0; i < num_total_lanes; i++) {

			if (!lanes[i].isEmpty()) {
	        	Shopper *first_shopper = &(lanes[i].front());
				first_shopper -> items_left--;

	        	// check if the shopper is finished
	        	if (first_shopper -> items_left == 0) {
	        		print(*first_shopper);
	        		lanes[i].dequeue();
	        		shoppers_finished++;
	        	}
	        }
        }

        // check if it is time to enqueue the first shopper in storage
        if (!storage.isEmpty() && storage.front().arrival_time == curr_time)
		    distribute(storage.front());
        curr_time++;
    }
}

// Insert any private functions below this line

// Function: populate_storage
// Input: reference to an instream address
// Returns: none
// Does: reads shoppers from infile and populates storage queue
void GrocerySim::populate_storage(istream &infile) {

	Shopper curr;
	int shopper_num = 1;

	// interprets stream as boolean conditional
    while (infile >> curr.arrival_time && infile >> curr.num_items) {
		
		// assigns/initializes shopper member variables
    	curr.id = shopper_num;
    	shopper_num++;
		curr.items_left = curr.num_items;

		// stores curr_shopper in shopper storage array
		storage.enqueue(curr);
		total_shoppers++;
	}
} 

// Function: print
// Input: reference to the shopper at the front of the checkout line
// Return: none
// Does: prints shopper info, properly formatted according to the spec
void GrocerySim::print(Shopper &first_shopper)
{
	cout << "Shopper " << first_shopper.id << " arrived at "	\
	<< first_shopper.arrival_time << " with " \
	<< first_shopper.num_items << ", took " \
	<< curr_time - first_shopper.arrival_time << " units" << endl;
}

// Function: distribute
// Input: reference to the current shopper just read in from the infile
// Output: none
// Does: distributes new shopper into shortest lane via enqueue function
void GrocerySim::distribute(Shopper &curr_shopper)
{
	int num_available_lanes = num_total_lanes;

	// if not eligible for express lane, restrict lane availability (only std)
	if (curr_shopper.num_items > max_exp_items)
		num_available_lanes = num_std_lanes;

	// find the lane with fewest shoppers
	int min_index = 0;
	int min = lanes[0].size();
	for (int i = 1; i < num_available_lanes; i++) {
		if (lanes[i].size() < min)
			min_index = i;
	}

	// enqueue the the shortest lane with the first shopper in storage
	lanes[min_index].enqueue(curr_shopper);
	storage.dequeue();

}
