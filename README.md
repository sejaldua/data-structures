# data-structures
COMP 15: data structures. Topics include arrays, linked lists, trees, graphs, dynamic storage allocation, recursion, and sorting.

HW1: as an introduction to C++, implement a `dynamic array` to keep track of a pirate and all its friends, then write data to a text file

HW2: apply knowledge of `linked lists` to help MBTA plan extensions for its Green Line service

HW3: apply knowledge of `queues and dynamic arrays` to distribute and process shoppers through a grocery store checkout line simulation

HW4: apply knowledge of `recursion and binary search trees` to implement a binary search tree that successfully handles and keeps track of all elements / children in it

HW5: apply knowledge of `graphs and the breadth-first search algorithm` to simulate the game of Six Degrees of Kevin Bacon (https://oracleofbacon.org/)

Proj1: Help a hypothetical Tufts biology lab with DNA sequencing. A DNA sequence consists of long chains made up of 4 unique nitrogenous bases: Adenine (A), Guanine (G), Cytosine (C), and Thymine (T). The task was to create a program that can process a series of requests from an input file. The three requests we had to accommodate were insert, query, and remove. The data structure of relevance for this project was `tries`, a special type of tree that lacks the invariant of being able to compare node data via inequalities. At this point in the semester, we had the requisite skills needed to be cognizant of time and space complexity and perform a basic big O algorithmic analysis.

Proj2: The purpose of this project was to design a program that behaves similarly to the Unix `grep` program. To implement a recursive search of all files in a working directory, searching through word by word for matches against a query word, a `hash table` was used. Students had to make the design choice whether to use `chaining` (open hashing) or `open addressing` (closed hashing). In the end, I ended up implementing a vector of vector of vectors and using chaining as my hashing method. I ended up implementing largeGutenberg in 1:15 seconds, which was well within the time limit of 10 minutes. This was my favorite assignment in COMP15, and it is something I am very proud of, especially because I had a breakthrough idea that came to me in my sleep. 😴 
