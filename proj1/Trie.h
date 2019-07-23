/*
 * Trie.h - delaration of Trie class
 * Sejal Dua
 * Comp 15 Fall 2018 
 * 31/October/2018
 * Project 1: The Biologist's Grep
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <iostream>

using namespace std;


class Trie {

public:
        // constructor
        Trie();

        // destructor
        ~Trie();

        // for debugging purposes – to be commented out later
        void inspect_root() const;

        void print_all_sequences() const;

        bool contains(string seq) const;

        void insert(string seq);
        
        bool remove(ostream &out, string seq);

        string query(ostream &out, string query_seq);

        int seq_count() const;


private:

		static const int ARRAY_SIZE = 4;

		struct TrieNode {

			// array of TrieNode pointesr to A, C, G, and T (in that order)
		    struct TrieNode *next[ARRAY_SIZE];

		    // denotes if the TrieNode represents the end of a sequence
		    bool end_of_sequence;
		};

	    // the root of the trie (starts as NULL)
	    TrieNode *root;

	    // for debugging purposes
	    void inspect_node(TrieNode *node) const;

	    // used by the destructor to delete nodes recursively
	    void post_order_delete(TrieNode *node);

	    void post_order_delete_subtree(TrieNode *parent);

	    void print_all_sequences(TrieNode *node, string seq) const;

	    bool is_leaf_node(TrieNode *node) const;

	   	bool contains(TrieNode *node, string seq) const;

	    void insertHelper(TrieNode *node, string seq);

	    Trie::TrieNode *initialize_leaf_node();

	    bool removeHelper(TrieNode *node, TrieNode *parent, string seq);

	    bool remove_leaf_node(TrieNode *node, TrieNode *parent);

	    int get_index(string seq) const;

	    string queryHelper(TrieNode *node, string query_seq, string &prefix, string &suffix) const;

	    int evaluate_match(string orig, string perfect_prefix, string best_match) const;

		Trie::TrieNode *get_longest_prefix(TrieNode* node, TrieNode *prev, string query_seq, string &prefix) const;

		string get_shortest_suffix(TrieNode *node) const;

		string get_longest_suffix(TrieNode *node) const;
		
	    int seq_count(TrieNode *node) const;

};



#endif /* TRIE_H_ */
