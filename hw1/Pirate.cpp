/*
 * Pirate.cpp
 * Sejal Dua
 * 17/September/2018
 * COMP 15 HW1
 * Fall 2018
 *
 * This is the implarrrrrrmentation of a Pirate. This file
 * includes a constructor, a parameterized constructor, a 
 * print function which specifies the Pirate's ID and name,
 * and some name generation functions which take an ifstream
 * reference and help us add pirates from a file.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pirate.h"
using namespace std;

int Pirate::pirate_count = 0;

Pirate::Pirate()
{
    pirate_id = -1;
    name = "Cap'n Hook";
}

Pirate::Pirate(string n)
{
    assign_pirate_id();
    name = n;
}


/*
 * Function print
 * Input: ostream object address of outfile
 * Returns: none
 * Does: Allows the client to print a pirate's identifying
 * information to a file, to standard out, to standard error, or
 * any other ostream type.
 */
void Pirate::print(ostream &outfile) const
{
    outfile << pirate_id << " "
         << name;
}

void Pirate::generate_pirate_name(ifstream &infile, int range)
{
    string pname;
    int rando = rand() % range;
    int count = 0;

    infile.clear();
    infile.seekg(0, ios::beg);
    while (getline(infile, pname))
    {
        if (count == rando)
        {
            name = pname;
            break;
        }
        count++;
    }
}

/*
 * Function generate_next_pirate
 * Input: ifstream object address of infile
 * Returns: none
 * Does: Systematically adds pirates from a file in consecutive
 * order. The getline function is used to extract a single line 
 * from the infile and store the contents in a string variable, 
 * which is ultimately assigned to the pirate's instance variable name.
 */
void Pirate::generate_next_pirate(ifstream &infile)
{
    string pname;
    getline(infile, pname);
    name = pname;
}

void Pirate::assign_pirate_id()
{
    pirate_id = pirate_count++;
}

bool operator == (const Pirate &p1, const Pirate &p2)
{
    return (p1.pirate_id == p2.pirate_id);
}

