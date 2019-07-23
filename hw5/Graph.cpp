/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "Graph.h"
#include "Stack.h"
#include "Actor.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor. Initializes with zero vertices
template<class Vertex>
Graph<Vertex>::Graph()
{
    curr_vertex = 0;
    edges = NULL;
    path = NULL;
    vertices = NULL;
    marks = NULL;
}

// Function: ~Graph
// Inputs: none
// Returns: nothing
// Does: destructor
template<class Vertex>
Graph<Vertex>::~Graph()
{
    destroy_graph();
}

// Function: destroy_Graph
// Inputs: none
// Returns: none
// Does: deletes and deallocates all memory occupied by array variables
template<class Vertex>
void Graph<Vertex>::destroy_graph()
{
    if (vertices == NULL) {
        return;
    }

    for (int i = 0; i < num_vertices; i++) {
        delete[] edges[i];
        edges[i] = NULL;
    }
    delete[] edges;
    edges = NULL;

    delete[] path;
    path = NULL;

    delete[] vertices;
    vertices = NULL;

    delete[] marks;
    marks = NULL;
}

// Function: Graph
// Parameters: integer number of vertices (size of graph)
// Returns: none
// Does: paramaterized constructor (initializes graph with num_v vertices)
template<class Vertex>
Graph<Vertex>::Graph(int num_v)
{
    initialize_graph(num_v);
}

// Function: Graph
// Inputs: const Graph object g (passed in by reference)
// Returns: none
// Does: copy constructor (deep copies attributes from g into this)
template<class Vertex>
Graph<Vertex>::Graph(const Graph &g)
{
    curr_vertex = g.curr_vertex;
    num_vertices = g.num_vertices;
    edges = new string*[num_vertices];
    vertices = new Vertex[num_vertices];
    path = new int[num_vertices];
    marks = new bool[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        edges[i] = new string[num_vertices];
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = g.edges[i][j];
        }
        vertices[i] = g.vertices[i];
        path[i] = g.path[i];
        marks[i] = g.marks[i];
    }
}

// Function: operator=
// Inputs: const Graph object source (passed in by reference)
// Returns: Graph<Vertex> object
// Does: assignment overload
template<class Vertex>
Graph<Vertex> &Graph<Vertex>::operator= (const Graph &source)
{
    // delete current graph attributes
    destroy_graph();

    // copy contents of source into this
    curr_vertex = source.curr_vertex;
    num_vertices = source.num_vertices;
    edges = new string*[num_vertices];
    vertices = new Vertex[num_vertices];
    path = new int[num_vertices];
    marks = new bool[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        edges[i] = new string[num_vertices];
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = source.edges[i][j];
        }
        vertices[i] = source.vertices[i];
        path[i] = source.path[i];
        marks[i] = source.marks[i];
    }

    // don't forget to "return *this"
    return *this;
}

// Function: initialize_graph
// Input: integer, number of vertices
// Returns: void
// Does: dynamically allocates all memory
//       for a graph of num_v vertices 
//       without any vertices
//       and prepares all DFS,BFS variables
template<class Vertex>
void Graph<Vertex>::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }
}

// Function: add_vertex
// Parameters: Vertex, by value
// Returns: void
// Does: Add a new vertex to the end of the 2d array
//       Initializes every from/to edge to be NULL
template<class Vertex>
void Graph<Vertex>::add_vertex(Vertex v)
{
    vertices[curr_vertex] = v;
    for (int i = 0; i < num_vertices; i++)
    {
        edges[curr_vertex][i] = NULL_EDGE;
        edges[i][curr_vertex] = NULL_EDGE;
    }
    curr_vertex++;
 }

// Function: add_edge
// Parameters: Two vertices, and integer (weight)
// Returns: void
// Does: Adds an edge between the two vertices and 
//       assigns their weight to their shared movie string
//       (in case the edge did not exist) 
 template<class Vertex>
 void Graph<Vertex>::add_edge(Vertex f, Vertex t, string movie)
 {
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    if (edges[row][col] == NULL_EDGE) {
        edges[row][col] = movie;
        edges[col][row] = movie;
    }
 }

// Function: get_edge
// Parameters: Two vertices
// Returns: string
// Does: Gets edge between the two vertices and returns their shared movie 
// as a string
 template<class Vertex>
 string Graph<Vertex>::get_edge(Vertex f, Vertex t) const
 {
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    if (edges[row][col] == NULL_EDGE)
        return "";
    else
        return edges[row][col];
 }

// Function: print_matrix
// Parameters: ostream
// Returns: void
// Does: Prints the 2d adjacency matrix of the graph
template <class Vertex>
void Graph<Vertex>::print_matrix(ostream & out) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
            out << edges[i][j] << " ";
        out << endl;
    }
}


// Function: clear_marks
// Parameters: none
// Returns: none
// Does: sets all the marks to be false
//       For algorithms that need to mark vertices (BFS, DFS)
template<class Vertex>
void Graph<Vertex>::clear_marks()
{
    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
    }
}

// Function: initialize_path
// Parameters: none
// Returns: none
// Does: sets every value in the predecessor path to be NULL edge
template<class Vertex>
void Graph<Vertex>::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

// Function: update_predecessor
// Parameters: Two vertices
// Returns: None
// Does: sets pred as the predecessor of curr in the path
//       (in case that curr did not have any predecessor)
//       Nothing otherwise.
template<class Vertex>
void Graph<Vertex>::update_predecessor(Vertex pred, Vertex curr)
{
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == pred)
            pred_index = i;
        if (vertices[i] == curr)
            curr_index = i;
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

// Function: report
// Inputs: bool found, ostream out object, start and end vertices
// Retruns: none
// Does: reports graph traversal path if one exists or says no connection 
// if there is no path that connects the two actors
template<class Vertex>
void Graph<Vertex>::report(bool found, ostream &out, Vertex a, Vertex b) const
{
    //Report path if a path was found connecting Vertex a to Vertex b
    if (found)
        report_path(out, a, b);

    // Prints that no connection was found between Vertex a and Vertex b
    else
        out << a << " and " << b << ": No connection" << endl << endl;
}

// Function: report_path
// Parameters: ostream to print, start and end vertices
// Returns: none
// Does: finds path from start to end and prints it
//       uses the information stored on predecessor path 
template<class Vertex>
void Graph<Vertex>::report_path(ostream &out, Vertex start, Vertex end) const
{
    Stack<Vertex> s;
    Stack<int> indices;
    int index = index_is(vertices, end);
    s.push(vertices[index]);
    indices.push(index);
    bool done = false;
    while (!done)
    {
        index = path[index];
        if (vertices[index] == start)
            done = true;
        s.push(vertices[index]);
        indices.push(index);
    }

    out << start << " and " << end << " have a costar distance of ";
    out << s.get_size()-1 << endl;

    while (!s.is_empty())
    {
        Vertex v1 = s.top();
        int a = indices.top();
        s.pop();
        indices.pop();
        if (!s.is_empty()) {
            Vertex v2 = s.top();
            int b = indices.top();
            string connection = edges[a][b];
            out << v1 << " was in " << connection << " with " << v2 << endl;
        }
    }
    out << endl;
}


// Function: mark_vertex
// Parameters: Vertex
// Returns: none
// Does: sets the mark of the given vertex to true
template<class Vertex>
void Graph<Vertex>::mark_vertex(Vertex v)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

// Function: is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns true if the vertex is marked
//       false otherwise
template<class Vertex>
bool Graph<Vertex>::is_marked(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

// Function: is_vertex
// Parameters: vertex
// Returns: bool
// Does: returns true if vertex exists in the graph,
//       false otherwise.
template <class Vertex>
bool Graph<Vertex>::is_vertex(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

// Function: get_to_vertices
// Parameters: Vertex, queue of vertices by reference
// Returns: void
// Does: Finds all neighbors of the the given vertex
//       enqueues all of its neighbors to the queue
 template<class Vertex>
 void Graph<Vertex>::get_to_vertices(Vertex v, Queue<Vertex> &adj) const
 {
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++)
        if (edges[from][to] != NULL_EDGE)
            if (vertices[to] != vertices[from])
                   adj.enqueue(vertices[to]);
}


// wrapper function definition
// Function: index_is
// Parameters: array of vertices, Vertex
// Returns: integer
// Does: Finds the target vertex in the list of vertices
//       returns the index of v
template<class Vertex>
int index_is(Vertex *vertices, Vertex v)
{
    int index = 0;
    while (!(v == vertices[index]))
        index++;
    return index;
}

// Function: BFS
// Inputs: Vertex a and Vertex b, ostream object out
// Returns: none
// Does: executes breadth-first search algorithm to traverse the graph
// from Vertex a to Vertex b and then report the path to out
// (Note: for better commenting, please see README)
template<class Vertex>
void Graph<Vertex>::BFS(Vertex a, Vertex b, ostream &out)
{
    clear_marks();
    initialize_path();
    if (!check_vertices(a, b, out))
        return;

    Queue<Vertex> primary;
    Queue<Vertex> neighbors;
    primary.enqueue(a);
    Vertex v1;
    bool found = false;
    while (!found)
    {
        // if there are no unvisisted vertices left, get out of while loop
        if (primary.is_empty())
            break;

        primary.dequeue(v1);

        // if vertex has not yet been visisted, time to process it
        if (!is_marked(v1)) {
            mark_vertex(v1);
            get_to_vertices(v1, neighbors);
            found = process_neighbors(primary, neighbors, v1, b);
        }
    }

    report(found, out, a, b);
}


// Function: process_neighbors
// Inputs: Vertex Queues called primary and neighbors, Vertices v1 and end
// Returns: bool value
// Does: processes neighbors, returns true if the end vertex is found, false
// if we need to explore a different route (keep processing primary)
template<class Vertex>
bool Graph<Vertex>::process_neighbors(Queue<Vertex> &primary, 
    Queue<Vertex> &neighbors, Vertex &v1, Vertex end)
{
    Vertex n1;

    // while there are neighbors to process, process them
    while (!neighbors.is_empty()) {

        // dequeue front element of neighbors, store it in n1
        neighbors.dequeue(n1);

        // if not visited before, update pred and save it for future processing
        if (!is_marked(n1)) {
            update_predecessor(v1, n1);   
            primary.enqueue(n1);
        }  

        // if we have found the end vertex, we can stop the algorithm!
        if (n1 == end)
            return true;
    }     

    // keep searching
    return false;
}

// Function: check_vertices
// Inputs: Vertex a and Vertex b, ostream object out
// Returns: bool value
// Does: returns false if either Vertex a or Vertex b is not a legitimate 
// in the graph (whichever comes first); otherwise, returns true to enable
// BFS algorithm to proeed
template<class Vertex>
bool Graph<Vertex>::check_vertices(Vertex a, Vertex b, ostream &out) const
{
    // if a is not a vertex in the graph
    if (!is_vertex(a)) {
        out << "Sorry, " << a << " is not in the list." << endl << endl;
        return false;
    }

    // if b is not a vertex in the graph
    else if (!is_vertex(b)) {
        out << "Sorry, " << b << " is not in the list." << endl << endl;
        return false;
    }

    // proceed with BFS algorithm
    else
        return true;
}

template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
template class Graph<Actor>;




