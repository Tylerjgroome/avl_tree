#include "../include/avl_tree.h"

// default avl_tree constructor
avl_tree::avl_tree(void) {
    max_height = 0;
    num_nodes = 0;
    root = NULL;
}

// avl_tree constructor with initial value
avl_tree::avl_tree(int value) {
    max_height = 1;

    node *n = new node;
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;

    setRootNode(n);

    num_nodes = 1;
}

// insert value into the AVL tree and self-balance
void avl_tree::insert(int value) {
    node *insert = insertHelper(root,value);
    if (insert != NULL) num_nodes++;
    return;
}

// get the root node of the tree
node * avl_tree::getRootNode(void) {
    return root;
}

// set the root node of the tree
void avl_tree::setRootNode(node *n) {
    root = n;
}

// get the maximum height of the tree
int avl_tree::getMaxHeight(void) {
    return max_height;
}

// set the maximum height of the tree
void avl_tree::setMaxHeight(int height) {
    max_height = height;
}

// get the number of nodes in the tree
int avl_tree::getNumNodes(void) {
    return num_nodes;
}

// AVL tree destructor, calls recursive private deleteNodes method
avl_tree::~avl_tree() {
    deleteNodes(root);
}