 /* Sejal Dua
  * COMP 15 FALL 2018
  * 15/November/2018
  * Homework 5: Graph Traversal
  *
  * Filename: test-graph.cpp
  * Contains: test
  * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
  *
  */

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>	/* time */
#include <fstream>

#include "Actor.h"
#include "Graph.h"

using namespace std;

int main()
{
	cout << "*** TEST 1: MAKING 3 ACTORS VIA PARAM CONSTRUCTOR *** " << endl;
	Actor a = Actor("Alice");
	Actor b = Actor("Bobby");
	Actor c = Actor("Charlotte");
	cout << "Actor a name: " << a.get_name() << endl;
	cout << "Actor b name: " << b.get_name() << endl;
	cout << "Actor c name: " << c.get_name() << endl;
	if (a == b)
		cout << "The actors are identical." << endl;
	else
		cout << "The actors are different." << endl;
	a.insert_movie("Monsters inc");
	a.insert_movie("Moneyball");
	a.insert_movie("Bend It Like Beckham");
	b.insert_movie("Monsters inc");
	b.insert_movie("The Internship");
	c.insert_movie("Daddy Day Care");
	c.insert_movie("The Internship");
	cout << "Connection from a to b is " << a.connect(b) << endl;
	cout << "Connection from b to c is " << b.connect(c) << endl;
	cout << "Connection from a to c is " << a.connect(c) << endl;
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 2: MAKING 2 ACTORS VIA DEFAULT CONSTRUCTOR ***" << endl;
	Actor d;
	Actor e;
	cout << "Actor d name: " << d.get_name() << endl;
	cout << "Actor e name: " << e.get_name() << endl;
	if (d == e)
		cout << "The actors are identical." << endl;
	else
		cout << "The actors are different." << endl;
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 3: TESTING AUXILIARY FUNCTIONS I WROTE ***" << endl;
	Graph<Actor> g1(3);
	cout << "added some vertices" << endl;
	g1.add_vertex(a);
	g1.add_vertex(b);
	g1.add_vertex(c);
	cout << "added some edges" << endl;
	g1.add_edge(a, b, a.connect(b));
	g1.add_edge(b, c, b.connect(c));
	cout << "testing get_edge" << endl;
	cout << "Edge (shared movie) b/w a and b: " << g1.get_edge(a, b) << endl;
	cout << "Edge (shared movie) b/w b and c: " << g1.get_edge(b, c) << endl;
	cout << "Edge (shared movie) b/w a and c: " << g1.get_edge(a, c) << endl;
	cout << "testing BFS, report, and report path" << endl;
	g1.BFS(a, c, cout);
	cout << "printing matrix..." << endl;
	g1.print_matrix(cout);
	cout << "Successful test" << endl << endl;

	
	cout << "*** TEST 4: TESTING ASSIGNMENT OVERLOAD ***" << endl;
	Graph<Actor> g2;
	g2 = g1;
	cout << "printing matrix..." << endl;
	g2.print_matrix(cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 5: TESTING COPY CONSTRUCTOR ***" << endl;
	Graph<Actor> g3 = g1;
	cout << "printing matrix..." << endl;
	g3.print_matrix(cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 6: TESTING TEMPLATING (Graph<int>) ***" << endl;
	Graph<int> ints(6);
	ints.add_vertex(2);
	ints.add_vertex(4);
	ints.add_vertex(6);
	ints.add_vertex(15);
	ints.add_vertex(25);
	ints.add_vertex(45);
	ints.add_edge(2, 4, "divisible by 2");
	ints.add_edge(2, 6, "divisible by 2");
	ints.add_edge(4, 6, "divisible by 2");
	ints.add_edge(6, 15, "divisible by 3");
	ints.add_edge(15, 25, "divisible by 5");
	ints.add_edge(15, 45, "divisible by 5");
	ints.add_edge(25, 45, "divisible by 5");
	cout << "printing matrix..." << endl;
	ints.print_matrix(cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 7: TEST WITH VERTICES AND NO EDGES ***" << endl;
	Graph<string> strs;
	string str_a = "I"; 
	string str_b = "am"; 
	string str_c = "so";
	string str_d = "tired";
	string str_e = "today";
	strs.initialize_graph(4);
	strs.add_vertex(str_a);
	strs.add_vertex(str_b);
	strs.add_vertex(str_c);
	strs.add_vertex(str_d);
	cout << "printing matrix..." << endl;
	strs.print_matrix(cout);
	strs.BFS(str_a, str_c, cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 8: TEST WITH VERTICES AND ONE EDGE ***" << endl;
	strs.add_edge(str_a, str_b, "subject and verb");
	cout << "printing matrix..." << endl;
	strs.print_matrix(cout);
	strs.BFS(str_a, str_b, cout);
	strs.BFS(str_a, str_c, cout);
	strs.BFS(str_c, str_d, cout);
	strs.BFS(str_d, str_e, cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 9: TEST WITH VERTICES AND MULTIPLE EDGES ***" << endl;
	ints.BFS(2, 45, cout);
	ints.BFS(3, 15, cout);
	ints.BFS(2, 15, cout);
	cout << "Successful test" << endl << endl;


	cout << "*** TEST 10: TEST WITH NULL GRAPH ***" << endl;
	Graph<Actor> g4;
	cerr << "default constructor worked" << endl;
	Graph<Actor> g5 = g4;
	cerr << "assignment overload worked" << endl;
	Graph<Actor> g6;
	g6 = g4;
	cerr << "copy constructor worked" << endl;
	g4.BFS(Actor("Hugh Grant"), Actor("Jennifer Lawrence"), cout);
	cout << "Successful test" << endl << endl;

	return 0;
}