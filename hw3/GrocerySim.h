/*
 * Sejal Dua
 * CheckoutQueue.h
 * COMP15 HW3
 * Fall 2018
 *
 * Interface of the GrocerySim class
 *
 */

#ifndef GROCERYSIM_H
#define GROCERYSIM_H
#include <istream>
#include <string>
#include <cstdio>
#include "shopper.h"
#include "CheckoutQueue.h"

using namespace std;

class GrocerySim
{
public:
	GrocerySim();
	GrocerySim(int num_standard_queue, int num_express, int max_express);
	~GrocerySim();
	void run (istream &infile);
private:

	CheckoutQueue *lanes;

	int num_std_lanes;
	int num_exp_lanes;
	int num_total_lanes;
	int max_exp_items;
	int curr_time;
	int total_shoppers;
	int shoppers_finished;

	CheckoutQueue storage;

	void populate_storage(istream &infile);
	void print(Shopper &first_shopper);
	void distribute(Shopper &curr_shopper);


};

#endif