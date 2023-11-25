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
    node *n = insertHelper(root,value);
    setRootNode(n);
    num_nodes++;
    updateMaxHeight();
    return;
}

// remove value from the AVL tree and self-balance
void avl_tree::remove(int value) {
    node *remove = removeHelper(root,value);
    if (remove != NULL) {
        num_nodes--;
    } else {
        std::cout << "Value " << value << " not found in AVL tree" << std::endl;
    }
    updateMaxHeight();
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

// get the number of nodes in the tree
int avl_tree::getNumNodes(void) {
    return num_nodes;
}

// print elements in tree in order
void avl_tree::printInOrder(void) {
    std::cout << "In order: " << std::endl;
    printInOrderHelper(root);
    std::cout << "\n";
}

// print elements in tree in post order
void avl_tree::printPostOrder(void) {
    std::cout << "Post order: " << std::endl;
    printPostOrderHelper(root);
    std::cout << "\n";
}

// print elements in tree in order
void avl_tree::printPreOrder(void) {
    std::cout << "Pre order: " << std::endl;
    printPreOrderHelper(root);
    std::cout << "\n";
}


// AVL tree destructor, calls recursive private deleteNodes method
avl_tree::~avl_tree() {
    deleteNodes(root);
}