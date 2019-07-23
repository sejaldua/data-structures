/*
 * evil.cpp
 * COMP15
 * Fall 2018
 *
 * Implementation of the Roster class
 *
 */

#include "roster.h"
#include "Student.h"
using namespace std;
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

/* Purpose: Default Constructor, initializes an empty roster */
Roster::Roster()
{
    list = new Student[20];
    capacity = 20;
    size = 0;
}

/* Purpose: Default Destructor, frees any heap-allocated memory */
Roster::~Roster()
{
    delete [] list;
}

/* Purpose: evil function created to change all the grades of the students */
void Roster::do_evil(char* filename)
{
    read_file(filename);
    change_grades();
    write_out(filename);
}

/* Purpose: Reads in all the student data from specified filename 
* and stores data in its private array list
* Parameters: Filename
* Returns: Nothing
*/
void Roster::read_file(char* filename)
{
    ifstream infile;
    infile.open(filename);
    string name;
    int grade;
    while(infile >> name && infile >> grade)
    {
        add_student(name, grade);
    }
    infile.close();
}

/* Purpose: Creates instance of type Student and adds to the array
* Parameters: Name and grade of student.
* Returns: Nothing
*/
void Roster::add_student(string name, int grade)
{
    if(size == capacity)
    {
        expand();
    }
    Student s;
    s.name = name;
    s.grade = grade;
    list[size] = s;
    size++;
}

/* Purpose: Changes grades of every student in array to 0.
* Parameters: Nothing
* Returns: Nothing
*/
void Roster::change_grades()
{
    for (int i = 0; i < size; i++)
    {
        list[i].grade = 0;
    }
}

/* Purpose: Writes the student information (name, grade) 
* from the array to into the given file.
* Parameters: Filename to write to
* Returns: Nothing
*/
void Roster::write_out(char* filename)
{
    ofstream outfile;
    outfile.open(filename);
    for (int i = 0; i < size; i++)
    {
        cout << "Just failed student " << (list[i]).name << ". Feels good!" << endl;
        outfile << (list[i]).name << " " << (list[i]).grade << endl;
    }
    outfile.close();
}

/* Purpose: Doubles array capacity
* Parameters: Nothing
* Returns: Nothing
*/
void Roster::expand()
{
    Student* temp = new Student[2 * capacity];
    for(int i = 0; i < size; i++)
    {
        temp[i] = list[i];
    }
    delete [] list;
    list = temp;
    capacity *= 2;
}