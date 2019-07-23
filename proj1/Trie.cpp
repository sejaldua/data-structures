// some comment

/* Sejal Dua
*/

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "Trie.h"

using namespace std;

static const string BASES = "ACGT";
static const char QUESTION_MARK = '?';
static const char ASTERISK = '*';

// Function: Trie 
// Inputs: none
// Returns: none
// Does: default constructor
Trie::Trie()
{
    root = initialize_leaf_node();
}

// Function: ~Trie
// Inputs: none
// Returns: none
// Does: destructor
Trie::~Trie()
{
	post_order_delete(root);
}

// Function: post_order_delete
// Inputs: TrieNode pointer called node
// Returns: none
// Does: deletes the whole tree from leaves to root, recursively
void Trie::post_order_delete(TrieNode *node)
{
    // check that node is not null
    if (node != NULL) {

        // recursively call post_order_delete on left and right branches
        for (int i = 0; i < ARRAY_SIZE; i++)
        	post_order_delete(node->next[i]);

        // delete node; set pointer to null so parent's pointer can be recycled
    	delete node;
    }
}

// Function: post_order_delete_subtree
// Inputs: TrieNode pointer called parent
// Returns: none
// Does: safely deletes a subtree, setting all of parent's pointers to null
void Trie::post_order_delete_subtree(TrieNode *parent)
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (parent->next[i] != NULL) {
        	post_order_delete_subtree(parent->next[i]);
        	delete parent->next[i];
			parent->next[i] = NULL;
		}
	}
}

// Function: inspect_root
// Inputs: none
// Returns: none
// Does: nicely prints out all of root's pointers; prints arrows if one of its
// next pointers is not null and just spaces if it is null
void Trie::inspect_root() const
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (root->next[i] == NULL)
			cout << BASES[i] << ":    " << endl;
		else
			cout << BASES[i] << ": -->" << endl;
	}

	if (is_leaf_node(root))
		cerr << "root has 4 null pointers" << endl;
}

// Function: inspect_node (private function for debugging purposes)
// Inputs: TrieNode pointer called node
// Returns: none
// Does: nicely prints out all of node's pointers; prints arrows if one of its
// next pointers is not null and just spaces if it is null
void Trie::inspect_node(TrieNode *node) const
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (node->next[i] == NULL)
			cout << BASES[i] << ":     " << endl;
		else
			cout << BASES[i] << ": -->" << endl;
	}
}

// Function: print_all_sequences
// Inputs: none
// Returns: none
// Does: prints all the sequences in the tree
void Trie::print_all_sequences() const
{
	print_all_sequences(root, "");
}

// Function: print_all_sequences
// Inputs: TrieNode pointer called node and seq string that will accrue letters
// Returns: none
// Does: prints all sequences in alphabetical order, starting from given node
void Trie::print_all_sequences(TrieNode* node, string seq) const
{
	if (node == NULL) 
		return;

	// if we are at the end of a sequence, cout the sequence
	else if (node->end_of_sequence) {
		cout << seq << endl;
	}

	// keep recursing through the subtree of the current node
	for (int i = 0; i < ARRAY_SIZE; i++)
		print_all_sequences(node->next[i], seq + BASES[i]);

}

// Function: is_leaf_node
// Inputs: TrieNode pointer called node
// Returns: bool value
// Does: checks if the node has 4 null pointers; returns
// true if leaf node, false if has child
bool Trie::is_leaf_node(TrieNode* node) const
{
	// iterates through array of next pointers
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (node->next[i] != NULL)
			return false;
	}

	return true;
}

// Function: contains
// Inputs: string seq
// Returns: bool value
// Does: checks if the passed in sequence is contained in the trie
bool Trie::contains(string seq) const
{
	return contains(root, seq);
}

// Function: contains
// Inputs: TrieNode pointer called node and the string seq we are looking for
// Returns: bool value
// Does: recursively traverses down a pathway in the trie and if the sequence
// formed by the pathway matches the query sequence, return true
bool Trie::contains(TrieNode *node, string seq) const
{
    
	// return false if the tree is empty
    if (node == NULL) {
    	return false;
    }

    // BASE CASE: we have found the complete sequence and it is identical!
    if (seq.length() == 0) {
    	if (node->end_of_sequence)
    		return true;
    }

    // recursively calls contains on A, C, G, and T subtrees
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
    	// if the first elem of the seq is the current base or a ?, recurse
    	if ((seq[0] == BASES[i]) or (seq[0] == QUESTION_MARK) or 
    		(seq[0] == ASTERISK))
    		return contains(node->next[i], seq.substr(1, seq.length()));
    }

    return false;
    
}

// Function: insert
// Inputs: string seq
// Returns: none
// Does: if the seq does not already exist in the trie, insert and 
// instantiate whatever nodes need to be inserted so that it does exist
void Trie::insert(string seq)
{
    if (!contains(seq))
    	insertHelper(root, seq);
}

// Function: insert
// Inputs: TrieNode pointer called node and seq string to be inserted
// Returns: none
// Does: recursively inserts nodes so that the string to be inserted
// exists in the tree, ensures that the sequence is properly stored by
// setting the final node's end of sequence bool to true
void Trie::insertHelper(TrieNode *node, string seq)
{
	// BASE CASE: seq is fully processed and we have traversed, mark end of seq
	if (seq.length() == 0) {
		node->end_of_sequence = true;
		return;
	}

	// chop off first char of string and check if corresponding TrieNode exists
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if ((seq[0] == BASES[i]) or (seq[0] == QUESTION_MARK)) {

			// if first elem of string array does not exist, insert a leaf node
			if (node->next[i] == NULL) {
				node->next[i] = initialize_leaf_node();
			}

			// recursively call insert w/ the remaining part of the sequence
			insertHelper(node->next[i], seq.substr(1));
		}
	}
}

// Function: initialize_leaf_node
// Inputs: none
// Returns: a TrieNode pointer to the new TrieNode object
// Does: allocates space for a new TrieNode object and intializes 
// its attributes to default values, finally returns a pointer to the object
Trie::TrieNode *Trie::initialize_leaf_node()
{
    // allocate space in memory for new Node object
    TrieNode *new_node = new TrieNode();

    // initialize attributes
    for (int i = 0; i < ARRAY_SIZE; i++)
    	new_node->next[i] = NULL;

    // default: not end of sequence (so that inserting a root works properly)
	new_node->end_of_sequence = false;

    // return pointer to new_node
    return new_node;
}

// Function: get_index
// Inputs: string seq
// Returns: int value
// Does: looks at the first char of seq and returns corresponding index 
// for ease of function calls
int Trie::get_index(string seq) const
{
	// NORMAL CASE: first letter in substring is a base --> return next index
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (seq[0] == BASES[i])
			return i;
	}

	// SPECIAL CASES
	if (seq[0] == QUESTION_MARK)
		return -1;
	else if (seq[0] == ASTERISK)
		return -2;

	// nonsensical return
	else
		return -10;

}

// Function: remove
// Inputs: string seq
// Returns: bool value
// Does: calls the recursive remove helper function if the given sequence
// currently exists in the trie
bool Trie::remove(ostream &out, string seq)
{
	if (contains(seq)) {
		out << seq << " removed" << endl;
		return removeHelper(root, root, seq);
	}
	else {
		out << seq << " Not found" << endl;
		return false;
	}
}

// Function: removeHelper
// Inputs: TrieNode ptr called node, TrieNode ptr called parent, string seq
// Returns: bool value
// Does: recursively removes the nodes that can be safely removed, returning
// true once the operation has been completed
bool Trie::removeHelper(TrieNode *node, TrieNode *parent, string seq)
{
	// BASE CASE: if node is null, return false
	if (node == NULL)
		return false;
	
	// keep recursively traversing through string
	if (seq.length() > 1) {
		for (int i = 0; i < ARRAY_SIZE; i++) {
			if ((seq[0] == BASES[i]) or (seq[0] == QUESTION_MARK))
				removeHelper(node->next[i], node, seq.substr(1));
			// SPECIAL CASE: asterisk
			else
				post_order_delete_subtree(node);
		}
	}

	// flip bool to false (lazy removal)
	node->end_of_sequence = false;

	// if node is a leaf node, actually remove it
	if (is_leaf_node(node) && (node != root))
		return remove_leaf_node(node, parent);
	else
		return true;
}

// Function: remove_leaf_node
// Inputs: TrieNode pointer called node, TrieNode parent called parent
// Returns: bool value
// Does: sets parent pointer to null and then removes node
bool Trie::remove_leaf_node(TrieNode *node, TrieNode *parent)
{
	// if parent is root, delete everything below root (just node)
	if (parent == root)
		post_order_delete_subtree(root);

	// sets all of parent's next pointers to null
	else {
		for (int i = 0; i < ARRAY_SIZE; i++) {
    		if (parent->next[i] == node)
        		parent->next[i] = NULL;
		}
	}

    // deletes and recycles the space node was occupying in memory
    delete node;
    return true;
}

// Function: evaluate_match
// Inputs: string orig, string perfect_prefix, string best_suffix
// Returns: float value
// Does: computes the formula given in the spec to assess how well the 
// string returned by query matches the original string
int Trie::evaluate_match(string orig, string prefix, string suffix) const
{
	return round((double)(prefix.length() * 100) / 
		(double)(max(orig.length(), (prefix+suffix).length())));
}

// Function: query
// Inputs: ostream object out and string query sequence
// Returns: string that is the closest match (see spec) to the query sequence
// Does: if the trie already contains the string we are querying, there
// is no need to use our query helper function, but if not, we enter
// the function and print the accuracy of our match to our ostream ref object
string Trie::query(ostream &out, string query_seq)
{
	// initialize variables we will be passing by reference
	string prefix = "";
	string suffix = "";

	// if the string exists (letter-for-letter) in trie, return it with pct
	if (contains(query_seq)) {
		out << "Match found " << query_seq << " 100%" << endl;
		return query_seq;
	}

	// call recursive query helper function and evaluate accuracy of match
	else {
		string match = queryHelper(root, query_seq, prefix, suffix);
		int pct_match = evaluate_match(query_seq, prefix, suffix);

		// matches the spec
		if (pct_match == 0)
			out << "No match found" << endl;
		else
			out << "Match found " << match << " " << pct_match << "%" << endl;
		return match;
	}

}

// Function: queryHelper
// Inputs: TrieNode pointer node, query string, prefix (ref), suffix (ref)
// Returns: string
// Does: splits the task into 2 parts: (1) find longest prefix (2) find best 
// suffix, settles ties according to tie-breaker prioritization highlighted
// in the spec
string Trie::queryHelper(TrieNode* node, string query_seq, string &prefix, 
	string &suffix) const
{
	// traverse down trie as far as we can according to the query string
	TrieNode* junction = get_longest_prefix(node, node, query_seq, prefix);

	// if the first char after junction = ?, prefix += result of queryHelper
	if (query_seq[prefix.length()] == QUESTION_MARK) {
		string options[ARRAY_SIZE]; int pcts[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; i++) {
			string temp_prefix = "";
			options[i] = queryHelper(junction->next[i], query_seq, 
				temp_prefix, suffix);
			pcts[i] = evaluate_match(query_seq, temp_prefix + BASES[i], suffix);
		}
		int max_index = 0;
		for (int i = 1; i < ARRAY_SIZE; i++) {
			if (pcts[i] > pcts[max_index])
				max_index = i;
		}
		prefix = prefix + options[max_index];
	}
	// if first char after junction = *, find the longest suffix
	else if (query_seq[prefix.length()] == ASTERISK)
		suffix = get_longest_suffix(junction).substr(1);
	else
		suffix = get_shortest_suffix(junction);

	return prefix + suffix;
}
	
// Function: get_longest_prefix
// Inputs: TrieNode pointers node and prev, string query_seq, prefix (ref)
// Returns: TrieNode pointer
// Does: updates the prefix passed in by reference and returns the TrieNode
// pointer that gets the furthest junction we can go down to
Trie::TrieNode* Trie::get_longest_prefix(TrieNode* node, TrieNode *prev, 
	string query_seq, string &prefix) const
{
	if (query_seq.length() == 0)
		return node;

	// if not 100% resemblance anymore, trim prefix and return previous node
    if (node == NULL) {
    	prefix = prefix.substr(0, prefix.length()-1);
    	return prev;
    }

    // spits out an index number corresponding to the first char of query_seq
    // note: makes my life easier so I don't have to write another for loop
    int index = get_index(query_seq);

    // question mark and asterisk cases - not exactly perfect if wild cards
	if (index == -1 or index == -2)
		return prev;

	// continue recursively traversing according to string
	else {
		prefix += BASES[index];
		return get_longest_prefix(node->next[index], node, query_seq.substr(1),
		 prefix);
	}

	// if we make it all the way through the query string, return the last node
    return node;
}

// Function: get_shortest_suffix
// Inputs: TrieNode pointer called node
// Returns: string
// Does: complicated recursive top-down approach which returns shortest suffix
// ACKNOWLEDGMENTS: Kevin
string Trie::get_shortest_suffix(TrieNode *node) const
{
	string curr_min;
	string abs_min;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if ((node->next[i] != NULL) && (node->next[i])->end_of_sequence) {
			abs_min = BASES[i];
			break;
		}
		else if (node->next[i] != NULL) {
			abs_min = BASES[i] + get_shortest_suffix(node->next[i]);
			break;
		}
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (node->next[i] != NULL && (node->next[i])->end_of_sequence)
			curr_min = BASES[i];
		else if (node->next[i] != NULL)
			curr_min = BASES[i] + get_shortest_suffix(node->next[i]);
		
		if (node->next[i] != NULL && curr_min < abs_min)
			abs_min = curr_min;
	}

	return abs_min;
}

// Function: get_longest_suffix
// Inputs: TrieNode pointer called node
// Returns: string
// Does: complicated recursive top-down approach which returns longest suffix
// note: this function is parallel to get_shortest suffix
// ACKNOWLEDGMENTS: Kevin
string Trie::get_longest_suffix(TrieNode *node) const
{
	string curr_max;
	string abs_max;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if ((node->next[i] != NULL) && (node->next[i])->end_of_sequence) {
			abs_max = BASES[i];
			break;
		}
		else if (node->next[i] != NULL) {
			abs_max = BASES[i] + get_longest_suffix(node->next[i]);
			break;
		}
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (node->next[i] != NULL && (node->next[i])->end_of_sequence)
			curr_max = BASES[i];
		else if (node->next[i] != NULL)
			curr_max = BASES[i] + get_shortest_suffix(node->next[i]);
		
		if (node->next[i] != NULL && curr_max > abs_max)
			abs_max = curr_max;
	}

	return abs_max;
}

// Function: seq_count
// Inputs: none
// Returns: int value
// Does: recursively traverses the tree, counting how many end of sequence
// markers (bools) and ultimately returns the amount of complete sequences
// stored in the trie
int Trie::seq_count() const
{
    return seq_count(root);
}

// Function: seq_count
// Inputs: a TrieNode pointer called node
// Returns: int value
// Does: returns the total number of complete sequences present in the tree
int Trie::seq_count(TrieNode *node) const
{
	// every time we get to the end of a seq, increment the running seq count
    int val = 0;

    if (node->end_of_sequence)
    	val++;

	// recursively increment node count and continue walking tree
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (node->next[i])
	    	val += seq_count(node->next[i]);
	}
    
    return val;

}


