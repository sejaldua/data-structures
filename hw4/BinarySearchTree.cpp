/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

// Function: BinarySearchTree 
// Inputs: none
// Returns: none
// Does: default constructor
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

// Function: ~BinarySearchTree
// Inputs: none
// Returns: none
// Does: destructor
BinarySearchTree::~BinarySearchTree()
{
    // walk tree in post-order traversal and delete
    post_order_delete(root);

    /* not really necessary, since the tree is going away, but might
    want to guard against someone using a pointer after deleting */
    root = NULL;   
}

// Function: post_order_delete
// Inputs: Node pointer called node
// Returns: none
// Does: deletes the whole tree from leaves to root, recursively
void BinarySearchTree::post_order_delete(Node *node)
{
    // check that node is not null
    if (node != NULL) {

        // recursively call post_order_delete on left and right branches
        post_order_delete(node->left);
        post_order_delete(node->right);

        // delete node; set pointer to null so parent's pointer can be recycled
        delete node;
        node = NULL;
    }
}

// Function: BinarySearchTree
// Inputs: const BinarySearchTree &source
// Returns: none
// Does: copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// Function: operator=
// Inputs: const BinarySearchTree &source
// Returns: "this" pointer / dereferenced binary search tree
// Does: assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    // check for self-assignment / alias
    if (this != &source) {

        // delete current tree if it exists
        post_order_delete(this->root);

        // use pre-order traversal to copy the tree
        this->root = pre_order_copy(source.root);
    }

    // don't forget to "return *this"
    return *this;
}       

// Function: pre_order_copy
// Inputs: Node pointer called node
// Returns: Node pointer
// Does: creates a new node with identical contents as the passed
// in node pointer and returns the node for copying purposes
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    // check if node is null
    if (node == NULL)
        return NULL;

    // alllocate space in memory for new node
    Node *new_node = new Node();

    // assign / copy node's content to new node's contents
    new_node->data = node->data;
    new_node->count = node->count;

    // recursive call on remaining children via left and right
    new_node->left = pre_order_copy(node->left);
    new_node->right = pre_order_copy(node->right);

    // return new node
    return new_node;
}

// Function: find_min
// Inputs: none
// Returns: minimum int value in the tree
// Does: calls recursive helper function to locate minimum node
// in the tree and then return its data; returns INT_MIN if tree is empty
int BinarySearchTree::find_min() const
{
    // check if the tree is empty
    if (root == NULL)
        return INT_MIN;

    // recursive helper call on root to eventually return min's data
    return find_min(root)->data;
}

// Function: find_min
// Inputs: Node pointer called node
// Returns: Node pointer that points to minimum (left-most) node in the tree
// Does: traverses the tree recursively until we have arrived at a leaf
// node such that the node's left is null, then returns that minimum node ptr
Node *BinarySearchTree::find_min(Node *node) const
{
    // if we have arrived at the min leaf node, return this min node
    if (node->left == NULL)
        return node;

    // recursively call find_min on the node's left child
    return find_min(node->left);
}

// Function: find_max
// Inputs: none
// Returns: maximum int value in the tree
// Does: calls recursive helper function to locate maximum node
// in the tree and then return its data; returns INT_MAX if tree is empty
int BinarySearchTree::find_max() const
{
    // check if the tree is empty
    if (root == NULL)
        return INT_MAX;

    // recursive helper call on root to eventually return max's data
    return find_max(root)->data;
}

// Function: find_max
// Inputs: Node pointer called node
// Returns: Node pointer that points to maximum (right-most) node in the tree
// Does: traverses the tree recursively until we have arrived at a leaf
// node such that the node's right is null, then returns that maximum node ptr
Node *BinarySearchTree::find_max(Node *node) const
{
    // if we have arrived at the max leaf node, return this max node
    if (node->right == NULL)
        return node;

    // recursively call find_max on the node's right child
    return find_max(node->right);
}

// Function: contains
// Inputs: int value
// Returns: (bool) true if value is in tree OR false if value is not in tree
// Does: calls recursive helper function to traverse tree in search of 
// passed in value and return a boolean variable depending on if the value
// is contained in the tree or not
bool BinarySearchTree::contains(int value) const
{
    // return false if the tree is empty
    if (root == NULL)
        return false;

    // recursive helper call on root to check if tree contains passed in value
    return contains(root, value);
}

// Function: contains
// Inputs: Node pointer called node and int value
// Returns: (bool) true if value is in tree OR false if value is not in tree
// Does: traverses tree until node either equals null or node's data is equal
// to the integer parameter value
bool BinarySearchTree::contains(Node *node, int value) const
{
    // return false if the tree is empty
    if (node == NULL) 
        return false;
    
    // recursively calls contains on left or right depending on traversal path
    if (node->data > value)
        return contains(node->left, value);
    else if (node->data < value)
        return contains(node->right, value);
    
    // returns true once we have escaped recursion (i.e. node's data == value)
    return true;
}

// Function: insert
// Inputs: int value
// Returns: none
// Does: calls recursive helper function which will insert the value 
// into the binary search tree; if the value already exists in the tree,
// the multiplicity count gets incremented
void BinarySearchTree::insert(int value)
{
    insert(root, NULL, value);
}

// Function: insert
// Inputs: Node pointer called node, Node pointer called parent, int value
// Returns: none
// Does: inserts the value into the binary search tree; if the value
// already exists in the tree, the multiplicity count gets incremented
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    // if node is null, allocate space in memory for node to be inserted 
    if (node == NULL) {
        node = initialize_leaf_node(value);

        // assign node a parent OR set node to be the root of the tree
        if (parent != NULL) {
            if (parent->data > node->data)
                parent->left = node;
            else
                parent->right = node;
        }
        else
            root = node;
        return;
    }

    // recursive traversing to find location for insertion
    if (node->data > value)
        insert(node->left, node, value);
    else if (node->data < value)
        insert(node->right, node, value);
    // if node already exists in tree, increment multiplicity count
    else
        (node->count)++;
}

// Function: initialize_leaf_node
// Inputs: int value that will eventually be stored as the new node's data
// Returns: a Node pointer to the new Node object
// Does: allocates space for a new Node object and intializes its attributes,
// finally returns a pointer to the object
Node *BinarySearchTree::initialize_leaf_node(int value)
{
    // allocate space in memory for new Node object
    Node *new_node = new Node();

    // initialize attributes
    new_node->data = value;
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    // return pointer to new_node
    return new_node;
}

// Function: remove
// Inputs: int value specifying node we wish to remove
// Returns: bool which tells us if the removal can be completed or not
// Does: calls recursive helper function which handles all edge cases
// we could have for a removal (e.g. deletion not possible, decrement 
// multiplicity, remove leaf node, remove node that has one child, remove
// node that has two children)
bool BinarySearchTree::remove(int value)
{
    return remove(root, NULL, value);
}

// Function: remove
// Inputs: a Node pointer called node, a Node pointer called parent, and
// an int value specifying which Node object we wish to remove
// Returns: bool which tells us if the removal can be completed or not
// Does: a full removal from the tree using the algorithms described in lecture
// case 1: node does not exist in tree --> return false (we are done)
// case 2: multiplicity is greater than 1 --> decrement count, no removal
// case 3: leaf node / no children --> remove node
// case 4: one child --> "bypass" the node to the child from the parent
// case 5: two children --> find maximum node of the left child, replace the 
// node's data with the value and count of left's maximum, then use find_parent
// to handle a clean and leak-free deletion of left's maximum.
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    // CASE 1: node to delete is not there - we are done!
    if (node == NULL)
        return false;

    // recursive traversals to find the node to remove
    if (node->data > value)
        remove(node->left, node, value);
    else if(node->data < value)
        remove(node->right, node, value);
    // removal of node (node->data == value)
    else {
        // CASE 2: multiplicity is greater than 1
        if (node->count > 1)
            (node->count)--;
        // CASE 3: leaf node
        else if (node->left == NULL && node->right == NULL)
            remove_leaf_node(node, parent); 
        // CASE 4: one child
        else if ((node->left != NULL) && (node->right == NULL))
            remove_one_child(node, node->left, parent);
        else if ((node->left == NULL) && (node->right != NULL))
            remove_one_child(node, node->right, parent);
        // CASE 5: 2 children
        else if ((node->left != NULL) && (node->right != NULL))
            remove_two_children(node);
    }
    return true;
}

// Function: delete_node
// Inputs: Node pointer called node
// Returns: none
// Does: deletes node and sets node to null to enable recycling of space
void BinarySearchTree::delete_node(Node *node)
{
    delete node;
    node = NULL;
}

// Function: remove_leaf_node
// Inputs: a Node pointer called node and a Node pointer called parent
// Returns: none
// Does: handles the removal procedure for if the node we wish to remove
// is a leaf node
void BinarySearchTree::remove_leaf_node(Node *node, Node *parent)
{
    // special case for if the root is the leaf node we will be removing
    if (node == root)
        root = NULL;

    // update the node parent's pointer
    else {
        if (parent->data > node->data)
            parent->left = NULL;
        else
            parent->right = NULL;
    }

    // delete and recycle the space node was occupying in memory
    delete_node(node);
}

// Function: remove_one_child
// Inputs: three Node pointers: node, parent, and child
// Returns: none
// Does: regardless of if we need to remove a left child or right child,
// we adjust parent's left or right pointer to be the child we have passed in
// and then go ahead and delete node
void BinarySearchTree::remove_one_child(Node *node, Node *child, Node *parent) 
{
    // special case for if the root is the one-child node we will be removing
    if (node == root)
        root = child;

    // update the node parent's pointer and then delete node
    else {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }

    // delete and recycle the space node was occupying in memory
    delete_node(node);
}

// Function: remove_two_children
// Inputs: a Node pointer called node
// Returns: none
// Does: finds the maximum of node's left child, replaces node's data with the
// data and count of the max node we have just found, and then finds 
// max's parent so that we may assign min's child or null ptr a new parent,
// and then we finally delete max via our private helper function delete_node
void BinarySearchTree::remove_two_children(Node *node)
{
    // finds the maximum of node's left child and the parent of max
    Node *max = find_max(node->left);
    Node *max_parent = find_parent(node, max);

    // copies / transfers contents from max to node
    node->data = max->data;
    node->count = max->count;

    // points max's parent to max's left, thereby bypassing max --> delete max
    remove_one_child(max, max->left, max_parent);
}

// Function: remove_two_children_min (*** ALTERNATE IMPLEMENTATION ***)
// Inputs: a Node pointer called node
// Returns: none
// Does: finds the minimum of node's right child, replaces node's data with the
// data and count of the min node we have just found, and then finds 
// min's parent so that we may assign min's child or null ptr a new parent,
// and then we finally delete min via our private helper function delete_node 
void BinarySearchTree::remove_two_children_min(Node *node) 
{
    // finds the minimum of node's right child and the parent of min
    Node *min = find_min(node->right);
    Node *min_parent = find_parent(node, min);

    // copies / transfers contents from min to node
    node->data = min->data;
    node->count = min->count;

    // points min's parent to min's right, thereby bypassing min --> delete min
    remove_one_child(min, min->right, min_parent);
}


// Function: tree_height
// Inputs: none
// Returns: int value specifying tree height
// Does: calls recursive helper function to calculate / evaluate the max 
// distance from root to farthest leaf
// Note - an empty tree has a height of -1, a tree with just a root has a 
// height of 0, and a tree with a root and 1 or 2 children has a height of 1
int BinarySearchTree::tree_height() const
{
    return tree_height(root);
}

// Function: tree_height
// Inputs: a Node pointer called node
// Returns: an int value specifying tree height
// Does: calculates / evalutes the maximum distance from root to farthest leaf
int BinarySearchTree::tree_height(Node *node) const
{
    if (node != NULL) {
        int left = tree_height(node->left);
        int right = tree_height(node->right);
        return 1 + max(left, right);
    }
    else
        return -1;

}

// Function: node_count
// Inputs: none
// Returns: an int value specifying the node count
// Does: calls a recursive helper function that counts the total number of
// Node obejcts present in the tree
int BinarySearchTree::node_count() const
{
    return node_count(root);
}

// Function: node_count
// Inputs: a Node pointer called node
// Returns: an int value specifying the node count
// Does: counts the total number of Node objects present in the tree
int BinarySearchTree::node_count(Node *node) const
{
    // checks if node equals null
    if (node == NULL)
        return 0;

    // recursively increment node count and continue walking tree
    return 1 + node_count(node->left) + node_count(node->right);
}

// Function: count_total
// Inputs: none
// Returns: an integer that is the sum of all node values (duplicates included)
// Does: calls recursive helper function to calculate the sum of all 
// the node values in the tree (including duplicates)
int BinarySearchTree::count_total() const
{
    return count_total(root);
}

// Function: count_total
// Inputs: none
// Returns: an integer that is the sum of all node values (duplicates included)
// Does: multiplies the count by the data of each node as the program 
// recursively traverses the tree; returns 0 if node equals null
int BinarySearchTree::count_total(Node *node) const
{
    // checks if node equals null
    if (node == NULL)
        return 0;

    // accesses the data of the node, accounting for any duplicates in count
    int val = (node->count) * (node->data);

    // recursively add to count total and continue walking tree
    return val + count_total(node->left) + count_total(node->right);
}

// Function: print_tree
// Inputs: none
// Returns: none
// Does: uses the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
    printPretty(root, 1, 0, std::cout);
}

// Function: find_parent
// Inputs: a Node pointer called node and a Node pointer called child
// Returns: a Node pointer representing the parent of the passed in "child"
// Does: invoked when removing a node that has two children; used to
// identify the parent of the min of the right node OR the parent of the
// max of the left node so that the parent's pointers can be oriented correctly
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL) 
        return NULL;

    // if either the left or right is equal to child, we have found the parent
    if ((node->left == child) or (node->right == child))
        return node;

    // use the binary search tree invariant to walk the tree
    if (child->data > node->data)
        return find_parent(node->right, child);
    else
        return find_parent(node->left, child);
}
