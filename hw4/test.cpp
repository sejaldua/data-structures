#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void print_tree_details(BinarySearchTree &bst)
{
        bst.print_tree();
        cout << "\n";
        cout << "min: "         << bst.find_min()    << "\n";
        cout << "max: "         << bst.find_max()    << "\n";
        cout << "nodes: "       << bst.node_count()  << "\n";
        cout << "count total: " << bst.count_total() << "\n";
        cout << "tree height: " << bst.tree_height() << "\n";
        cout << "\n";
}

int main()
{
    BinarySearchTree bst;
    int values[]  = {6, 6, 2, 8, 1, 5, 5, 15, 13, 14};
    int numValues = sizeof(values) / sizeof(int);


    for (int i = 0; i < numValues; i++) {
            bst.insert(values[i]);
    }
    cout << "Original tree "
         << "(asterisks denote a count of more than 1):\n";
    print_tree_details(bst);

    cout << "Removing 6 from tree:\n";
    bst.remove(6);
    print_tree_details(bst);

    cout << "Removing 6 from tree:\n";
    bst.remove(6);
    print_tree_details(bst);

    cout << "Removing 13 from tree:\n";
    bst.remove(13);
    print_tree_details(bst);

    cout << "Removing 14 from tree:\n";
    bst.remove(14);
    print_tree_details(bst);

    cout << "Removing 5 from tree:\n";
    bst.remove(5);
    print_tree_details(bst);

    cout << "Removing 8 from tree:\n";
    bst.remove(8);
    print_tree_details(bst);

    cout << "Removing 15 from tree:\n";
    bst.remove(15);
    print_tree_details(bst);

    cout << "Removing 13 from tree:\n";
    bst.remove(13);
    print_tree_details(bst);

    cout << "Removing 1 from tree:\n";
    bst.remove(1);
    print_tree_details(bst);

    cout << "Removing 2 from tree:\n";
    bst.remove(2);
    print_tree_details(bst);

    cout << "Removing 5 from tree:\n";
    bst.remove(5);
    print_tree_details(bst);

    cout << "Removing 20 from tree:\n";
    bst.remove(20);
    print_tree_details(bst);

    return 0;


}