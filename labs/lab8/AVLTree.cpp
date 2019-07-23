/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for COMP15
 * Part of: Lab assignment "AVL Trees" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "AVLTree.h"

using namespace std;


/* 
 * Input: data (the value to store), height of the node, left and 
 *       right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
*/
static Node *newNode(int data, int height, Node *left, Node *right)
{
        Node *np = new Node();
    
        np->data  = data;
        np->height = height;
        np->left  = left;
        np->right = right;

        return np;
} 


/* 
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new nodewith default
 *        values parameter
*/
static Node *newNode(int data)
{
        return newNode(data, 0, NULL, NULL);
}



/* 
 * Input: the node to be deleted.
 * Returns: N/A
 * Does: Set node contents to predictable, "deleted" node values
 *       and then recycle the node.
*/
static void deleteNode(Node *np)
{
        np->height = -1;  /* Something that couldn't be in a real node */
        np->data  = -1;  /* Arbitrary value                           */
        np->left  = np->right = NULL;
        delete 
        np;
}



/* 
 * Input: N/A
 * Returns: AVL class object
 * Does: Sets the root node to NULL
*/
AVLTree::AVLTree()
{
        root = NULL;
}

/* 
 * Input: N/A
 * Returns: N/A
 * Does: Deletes the AVL tree clears the memory used. Resets the root pointer
*/
AVLTree::~AVLTree()
{
        /* walk tree in post-order traversal and delete */
        post_order_delete(root);
        root = NULL;   /* not really necessary, since the tree is going 
                        away, but might want to guard against someone
                        using a pointer after deleting */
}


/* 
 * Input: a node of an AVL tree
 * Returns: N/A
 * Does: Deletes the AVL tree of node in a post order manner.
*/
void AVLTree::post_order_delete(Node *node)
{
        if (node != NULL) {
                post_order_delete(node->left);
                post_order_delete(node->right);
                deleteNode(node);
        }
}


/* 
 * Input: an integer value to be inserted in the AVL tree
 * Returns: N/A
 * Does: Calls a helper function to insert the given value in the tree.
*/
void AVLTree::insert(int value)
{
        root = insert(root, value);
}


/* 
 * Input: Node np - a node of the avl tree. value - an integer value to 
 *         be inserted in the AVL tree
 * Returns: the updated subtree of np.
 * Does: Inserts within a AVL tree the given value, while maintaining the 
 *        AVL invarient 
*/
Node *AVLTree::insert(Node *np, int value)
{
        /* BST insertion start */
        if (np == NULL) {
                return newNode(value);

        } else if (value < np->data) {
                np->left = insert(np->left, value);
        
        } else if (value > np->data) {
                np->right = insert(np->right, value);
        } else if (value == np->data) {
        	return np;
        }
        /* BST insertion ends */

        /* AVL maintenance start */
        np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));
        np = balance (np);
        /* AVL maintenace end */

        return np;
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: the balanced subtree of np.
 * Does: If unbalanced, balances the subtree of node.
*/
Node *AVLTree::balance(Node *np) 
{
    // CASES 1 and 2: left child
    if (heightDiff(np) > 1) {

        // CASE 2: right subtree
        if (heightDiff(np->left) < 0)
            np->left = leftRotate(np->left);

        // CASE 1: just left subtree
        return rightRotate(np);
    }

    // CASES 3 and 4: right child
    else if (heightDiff(np) < -1) {
        
        // CASE 4: left subtree
        if (heightDiff(np->right) > 0)
            np->right = rightRotate(np->right);

        // CASE 3: just right subtree
        return leftRotate(np);
    }

    return np;
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
*/
Node *AVLTree::rightRotate(Node *np) 
{ 
    Node *b = np->left;
    Node *a = b->right;

    // swapping of pointers
    b->right = np;
    np->left = a;

    // update heights
    np->height = max(nodeHeight(np->left), nodeHeight(np->right)) + 1;
    b->height = max(nodeHeight(b->left), nodeHeight(b->right)) + 1;

    return b;


} 
  
/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
*/
Node *AVLTree::leftRotate(Node *np) 
{ 
    Node *b = np->right;
    Node *a = b->left;

    // swapping of pointers
    b->left = np;
    np->right = a;

    // update heights
    np->height = max(nodeHeight(np->left), nodeHeight(np->right)) + 1;
    b->height = max(nodeHeight(b->left), nodeHeight(b->right)) + 1;

    return b;
} 



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer value signifying the height difference.
 * Does: calculates the difference in the height of the left and child 
 *       subtree of np
*/
int AVLTree::heightDiff(Node *np)
{
        int l_height = nodeHeight (np->left);
        int r_height = nodeHeight (np->right);

        int b_factor= l_height - r_height;
        return b_factor;
}



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer denoting the height attribute
 * Does: a getter to get the value of the height attribute.
*/
int AVLTree::nodeHeight(Node *node) 
{ 
        if (node == NULL) 
                return -1; 
        return node->height; 
} 


/* 
 * Input: value to be removed from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
 *       with the help of a helper function.
*/
bool AVLTree::remove(int value)
{
    return remove(root, NULL, value);
}

/* 
 * Input: Node np - a node of the avl tree. value to be removed 
 * from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
*/
bool AVLTree::remove(Node *node, Node *parent, int value)
{
    // heavily drawn from BST remove function (HW4)

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
        // CASE 2: leaf node
        if (node->left == NULL && node->right == NULL)
            remove_leaf_node(node, parent); 
        // CASES 3 and 4: one child
        else if ((node->left != NULL) && (node->right == NULL))
            remove_one_child(node, node->left, parent);
        else if ((node->left == NULL) && (node->right != NULL))
            remove_one_child(node, node->right, parent);
        // CASE 5: 2 children
        else if ((node->left != NULL) && (node->right != NULL))
            remove_two_children(node);
    }

    // balance parent subtree if balance invariant was affected by removal
    if (parent != NULL) {
        parent->height = 1 + max(nodeHeight(parent->left), nodeHeight(parent->right));
        parent = balance(parent);
    }

    return true;
}

void AVLTree::delete_node(Node *node)
{
    delete node;
    node = NULL;
}

// Function: remove_leaf_node
// Inputs: a Node pointer called node and a Node pointer called parent
// Returns: none
// Does: handles the removal procedure for if the node we wish to remove
// is a leaf node
void AVLTree::remove_leaf_node(Node *node, Node *parent)
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
void AVLTree::remove_one_child(Node *node, Node *child, Node *parent) 
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
void AVLTree::remove_two_children(Node *node)
{
    // finds the maximum of node's left child and the parent of max
    Node *max = find_max(node->left);
    Node *max_parent = find_parent(node, max);

    // copies / transfers contents from max to node
    node->data = max->data;

    // points max's parent to max's left, thereby bypassing max --> delete max
    remove_one_child(max, max->left, max_parent);
}

// Function: find_parent
// Inputs: a Node pointer called node and a Node pointer called child
// Returns: a Node pointer representing the parent of the passed in "child"
// Does: invoked when removing a node that has two children; used to
// identify the parent of the min of the right node OR the parent of the
// max of the left node so that the parent's pointers can be oriented correctly
Node *AVLTree::find_parent(Node *node, Node *child) const
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

int AVLTree::find_max() const
{
    // check if the tree is empty
    if (root == NULL)
        return INT_MAX;

    // recursive helper call on root to eventually return max's data
    return find_max(root)->data;
}

Node *AVLTree::find_max(Node *node) const
{
    // if we have arrived at the max leaf node, return this max node
    if (node->right == NULL)
        return node;

    // recursively call find_max on the node's right child
    return find_max(node->right);
}

/* 
 * Input: N/A
 * Returns: N/A
 * Does: uses a helper function to print a pretty tree.
*/
void AVLTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}