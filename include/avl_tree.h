#pragma once
#include <iostream>

// node struct
struct node {
    int value;
    int height;
    node *left;
    node *right;
};

class avl_tree {
    public:
        // default empty constructor
        avl_tree(void);

        // constructor that initialises root node of tree with value
        avl_tree(int value);

        // function to insert value into tree
        void insert(int value);

        // function to remove value from tree
        void remove(int value);

        // function to get the root node from the tree
        node *getRootNode(void);
        
        // function to get the height of the tree
        int getMaxHeight(void);

        // function to get the number of nodes from the tree
        int getNumNodes(void);

        // function to traverse, and print, the tree in order
        void printInOrder(void);

        // function to travserse, and print, the tree pre order
        void printPreOrder(void);

        // function to traverse, and print, the tree post order
        void printPostOrder(void);

        // function to check the existence of a value in the tree
        bool check(int value);

        // function to find the node with a particular value in the tree
        node* findNode(int value);

        // avl tree destructor (deletes all nodes in the tree)
        ~avl_tree();
    private:
        int num_nodes; // number of nodes in the tree
        int max_height; // height of the tree
        node *root; // root node

        // set the root node of the tree
        void setRootNode(node *n);

        // create a new node with value
        node *createNode(int value);

        // function to get the height of a node, if it exists
        int getHeight(node *n);

        // function to get the balance factor of a node, if it exists
        int getBalance(node* n);

        // convenience function to return the maximum of integers a and b
        int max(int a, int b);

        // right rotation function
        node *rightRotation(node * y);

        // left rotation function
        node *leftRotation(node * x);

        // function to update the height of the tree
        void updateMaxHeight();

        // recursive insert function helper
        node *insertHelper(node* n, int value);

        // function to get the node of minimum value in the tree
        node * minValueNode(node * n);

        // recursive remove helper function
        node *removeHelper(node* n, int value);

        // function to recursively delete all nodes in the AVL tree (on ~AVL_tree() call)
        node *deleteNodes(node *n);

        // helper function to print in order
        void printInOrderHelper(node *n);

        // helper function for print post order
        void printPostOrderHelper(node *n);

        // helper function for print pre order
        void printPreOrderHelper(node *n);
};