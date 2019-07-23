/*
 * testCheckoutQueue.cpp
 * Sejal Dua
 * 1/October/2018
 * COMP15 HW3
 * Fall 2018
 *
 * Test for CheckoutQueue.cpp. Initializes an empty checkout queue and some
 * shoppers. It then enqueues and prints information for all the shoppers. 
 * Through all this, it should be testing if the expand function is working
 * because the enqueue function will need to call the expand function if the
 * capacity is not big enough to enqueue another shopper. It then dequeues 
 * all shoppers except for one, and since dequeue-ing takes place at the
 * front, shopper 4 should remain. This hypothesis is verified, and then 
 * isEmpty is finally called to ensure that the dequeuing process went through
 * without a hitch!
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;

int main() {

    // intialize an empty checkout queue
    CheckoutQueue cq;

    // make sure it is empty
    cout << "I have just made a checkout queue!" << endl;
    cout << "-----------------------------------" << endl;
    cout << "THIS IS A TEST " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Empty Check: " << cq.isEmpty() << endl;

    // initalize some shoppers
    Shopper s1, s2, s3, s4;

    s1.id = 1;
    s1.arrival_time = 1;
    s1.num_items = 6;
    s1.items_left = 6;

    s2.id = 2;
    s2.arrival_time = 2;
    s2.num_items = 12;
    s2.items_left = 12;

    s3.id = 3;
    s3.arrival_time = 5;
    s3.num_items = 3;
    s3.items_left = 3;

    s4.id = 4;
    s4.arrival_time = 10;
    s4.num_items = 11;
    s4.items_left = 11;

    // enqueue shopper 1
    cq.enqueue(s1);
    
    // print information
    cout << "Shopper " << s1.id << endl;
    cout << "Num Shopper Items: " << s1.num_items << endl;
    cout << "Size of Queue: " << cq.size() << endl;
    cout << "Total Items: " << cq.totalItems() << endl;
    cout << "-----------------------------------" << endl;

    // enqueue shopper 2
    cq.enqueue(s2);
    
    // print information
    cout << "Shopper " << s2.id << endl;
    cout << "Num Shopper Items: " << s2.num_items << endl;
    cout << "Size of Queue: " << cq.size() << endl;
    cout << "Total Items: " << cq.totalItems() << endl;
    cout << "-----------------------------------" << endl;

    // enqueue shopper 3
    cq.enqueue(s3);
    
    // print information
    cout << "Shopper " << s3.id << endl;
    cout << "Num Shopper Items: " << s3.num_items << endl;
    cout << "Size of Queue: " << cq.size() << endl;
    cout << "Total Items: " << cq.totalItems() << endl;
    cout << "-----------------------------------" << endl;

    // test the private expand function of CheckoutQueue by exceeding capacity
    cq.enqueue(s4);
    
    // print information
    cout << "Shopper " << s4.id << endl;
    cout << "Num Shopper Items: " << s4.num_items << endl;
    cout << "Size of Queue: " << cq.size() << endl;
    cout << "Total Items: " << cq.totalItems() << endl;
    cout << "-----------------------------------" << endl;

    // print queue size
    cout << "Queue Size After Expand: " << cq.size() << endl;
    cout << "-----------------------------------" << endl;

    // dequeue the first three shoppers we added (s1, s2, s3), leaving just s4
    for (int i = 0; i < 3; i++) {
        cq.dequeue();
    }

    // print information of new shopper at the front (shopper 4)
    cout << "New Front of Queue: " << endl;
    cout << "Shopper " << cq.front().id << endl;
    cout << "Num Shopper Items: " << cq.front().num_items << endl;
    cout << "Size of Queue: " << cq.size() << endl;
    cout << "Total Items: " << cq.totalItems() << endl;
    cout << "-----------------------------------" << endl;

    cq.dequeue();

    // check if the queue is empty
    cout << "Empty Check: " << cq.isEmpty() << endl;

    // done
    cout << "-----------------------------------" << endl;
    cout << "All done!" << endl;
}