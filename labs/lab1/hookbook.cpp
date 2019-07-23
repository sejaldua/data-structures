// Sejal Dua
// 09/11/2018
// COMP15

// Lab 1
//

#include <iostream>
#include "Pirate.h"
#include "ArrayList.h"
using namespace std;

int main()
{
// Part 1: instantiating pirates
Pirate p1("Tim"), p2("George"), p3("Roger"), p4("Sheldon"), p5("Mark");
ArrayList arr;
arr.insert_pirate(p1);
arr.insert_pirate(p2);
arr.insert_pirate(p3);
arr.insert_pirate(p4);
arr.insert_pirate(p5);
arr.print();

//Part 2: adding extra commands to driver
ifstream infile;
infile.open("pirate_names.txt");
if(!infile.is_open()) {
	cout << "Error!" << endl;
}
ArrayList randlist;
for (int i = 0; i < 200; i++) {
	Pirate p;
	p.generate_next_pirate(infile, 200);
	p.assign_pirate_id();
	if (!randlist.is_full()){
		randlist.insert_pirate(p);
	}
}
randlist.print();
infile.close();

return 0;
}

