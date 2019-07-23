/*
 * evil.cpp
 * COMP15
 * Fall 2018
 *
 * Class declaration for Roster
 *
 */
 #ifndef ROSTER
#define ROSTER

#include <iostream>
using namespace std;
#include "Student.h"

class Roster{
    public:
        Roster();
        ~Roster();
        void do_evil(char* filename);
    private:
        Student* list;
        int capacity;
        int size;
        void read_file(char* filename);
        void write_out(char* filename);
        void change_grades();
        void add_student(string name, int grade);
        void expand();
};

#endif