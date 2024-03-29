/*
 * Sejal Dua
 * COMP 15 FALL 2018
 * 15/November/2018
 * Homework 5: Graph Traversal
 *
 * Filename: Nodetype.h
 * Contains: Interface of the template NodeType class (a node of a linked list) 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 */

#ifndef NODE_TYPE_H_
#define NODE_TYPE_H_

template<class E>
struct NodeType
{
    E info;
    NodeType<E> *next;
};

#endif
