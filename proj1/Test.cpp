#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>	/* time */
#include <fstream>

#include "Trie.h"

using namespace std;

int main()
{
	Trie trie;
    //string seqs[]  = {"AAT", "AA", "CAT", "GAG", "G", "GTA", "ACT", "TAT", "CAGTC", "GTGGGG", "TA?", "TA?C"};
    string seqs[] = {"CAAAA", "A", "AAC", "AA", "AAACAC", "AAAGTAC", "AAAT", "AAAG", "AAAC"};
	//string seqs[] = {"AAACG", "AAACGA", "AAAG"};
    //string seqs[] = {"TACAGGT", "TACAGGT", "T?G??GA"};

    for (string str : seqs) {
    	cout << "-------------------------------" << endl;
    	cout << "*** Inserting " << str << " ***" << endl;
    	cerr << "contains: " << trie.contains(str) << endl;
    	trie.insert(str);
    	trie.inspect_root();
    	cerr << "contains: " << trie.contains(str) << endl;
    }

    trie.print_all_sequences();
    cerr << "words in tree: " << trie.seq_count() << endl;

	string query_strings[] = {"ACCATAC", "TAA"};
    for (string str : query_strings) {
        cout << "-------------------------------" << endl;
        cout << "*** Querying... " << str << " ***" << endl;
    	trie.query(cout, str);
    }

    for (string str : seqs) {
    	cout << "-------------------------------" << endl;
    	cout << "*** Removing " << str << " ***" << endl;
    	cerr << "contains: " << trie.contains(str) << endl;
    	trie.remove(cout, str);
    	trie.inspect_root();
    	cerr << "contains: " << trie.contains(str) << endl;
    }
    
    // // example execution 1
    // trie.insert("TACAGGT");
    // trie.insert("T?G??GA");
    // trie.query("ACCATAC");
    // trie.insert("ACCATAC");
    // trie.query("TAC");
    // trie.insert("TAC");
    // trie.query("TC*");
    // trie.remove("TAC");

}
