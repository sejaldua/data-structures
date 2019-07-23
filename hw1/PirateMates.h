/*
 * PirateMates.h
 * Sejal Dua
 * 17/September/2018
 * COMP 15 HW1
 * Fall 2018
 * 
 * Interface for a struct of mates
 */

#include <iostream>
#include "Pirate.h"
#include "ArrayList.h"
using namespace std;

struct PirateMates
{
	Pirate pirate;
	ArrayList mates;
};