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
        void avl_tree::setRootNode(node *n) {
            root = n;
        }

        // create a new node with value
        node *createNode(int value) {
            node *new_node = new node;
            new_node->value = value;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->height = 1; // added to bottom of tree
            
            return new_node;
        }

        // function to get the height of a node, if it exists
        int getHeight(node *n) {
            if (n == NULL) {
                return 0;
            }

            return n->height;
        }

        // function to get the balance factor of a node, if it exists
        int getBalance(node* n) {
            if (n == NULL) {
                return 0;
            }

            return getHeight(n->left) - getHeight(n->right);
        }

        // convenience function to return the maximum of integers a and b
        int max(int a, int b) {
            return (a > b) ? a : b;
        }

        // right rotation function
        node *rightRotation(node * y) {
            node *x = y->left;
            node *T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = 1 + max(getHeight(y->left),getHeight(y->right));
            x->height = 1 + max(getHeight(x->left),getHeight(x->right));

            return x;
        }

        // left rotation function
        node *leftRotation(node * x) {
            node *y = x->right;
            node *T2 = y->left;
            
            y->left = x;
            x->right = T2;

            x->height = 1 + max(getHeight(x->left),getHeight(x->right));
            y->height = 1 + max(getHeight(y->left),getHeight(y->right));
            
            return y;
        }

        // function to update the height of the tree
        void updateMaxHeight() {
            max_height = getRootNode()->height;
        }

        // recursive insert function helper
        node *insertHelper(node* n, int value) {
    
            if (n == NULL) {
                // insert must occur here
                node *n = createNode(value);
                if (root == NULL) {
                    // empty tree
                    root = n;
                }
                return n;
            }

            if (n->value < value) {
                n->right = insertHelper(n->right,value);
            } else if (n->value > value) {
                n->left = insertHelper(n->left,value);
            } else {
                // no duplicates allowed
                std::cout << "Duplicate value ignored" << std::endl;
                num_nodes--;
                return n;
            }

            n->height = max(getHeight(n->left),getHeight(n->right)) + 1;

            int balance_factor = getBalance(n);

            if (balance_factor > 1 && n->left->value > value) return rightRotation(n);
            if (balance_factor < -1 && n->right->value < value) return leftRotation(n);

            if (n->left != NULL && balance_factor > 1 && n->left->value < value) {
                n->left = leftRotation(n->left);
                return rightRotation(n);
            }

            if (n->right != NULL && balance_factor < -1 && n->right->value > value) {
                n->right = rightRotation(n->right);
                return leftRotation(n);
            }

            return n;
        };

        // function to get the node of minimum value in the tree
        node * minValueNode(node * n) {
            node *curr = n;

            while (curr->left != NULL) {
                curr = curr->left;
            }

            return curr;
        }

        // recursive remove helper function
        node *removeHelper(node* n, int value) {
    
            if (n == NULL) {
                // value does not exist in the tree
                return n;
            }

            if (n->value < value) {
                n->right = removeHelper(n->right,value);
            } else if (n->value > value) {
                n->left = removeHelper(n->left,value);
            } else {
                // value found
                
                if (n->left == NULL || n->right == NULL) {
                    // if n->left exists choose it, else chose n->right
                    node *temp = n->left ? n->left : n->right;

                    if (temp == NULL) {
                        // if n->right is also NULL
                        temp = n;
                        n = NULL;
                    } else {
                        *n = *temp;
                    }

                    delete temp;
                } else {
                    node *temp = minValueNode(n->right);

                    n->value = temp->value;

                    n->right = removeHelper(n->right,temp->value);
                }
            }

            if (n == NULL) {
                // last node removed case
                return n;
            }

            n->height = max(getHeight(n->left),getHeight(n->right)) + 1;

            int balance_factor = getBalance(n);

            if (balance_factor > 1 && getBalance(n->left) >= 0) return rightRotation(n);
            if (balance_factor > 1 && getBalance(n->left) < value) {
                n->left = leftRotation(n->left);
                return rightRotation(n);
            }

            if (balance_factor < -1 && getBalance(n->right) <= 0) {
                return leftRotation(n);
            }

            if (balance_factor < -1 && getBalance(n->right) > 0) {
                n->right = rightRotation(n->right);
                return leftRotation(n);
            }

            return n;
        }

        // function to recursively delete all nodes in the AVL tree (on ~AVL_tree() call)
        node *deleteNodes(node *n) {
            // n is initially the root node

            if (n->left == NULL && n->right == NULL) {
                delete n;
                return NULL;
            }

            if (n->left == NULL && n->right != NULL) {
                n->right = deleteNodes(n->right);
            } else if (n->left != NULL && n->right == NULL) {
                n->left = deleteNodes(n->left);
            } else {
                n->left = deleteNodes(n->left);
            }

            return n;
        };

        // helper function to print in order
        void printInOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }

            printInOrderHelper(n->left);
            
            std::cout << n->value << " ";

            printInOrderHelper(n->right);
        }

        // helper function for print post order
        void printPostOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }

            printPostOrderHelper(n->left);

            printPostOrderHelper(n->right);

            std::cout << n->value << " ";
        }

        // helper function for print pre order
        void printPreOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }
            
            std::cout << n->value << " ";

            printPreOrderHelper(n->left);

            printPreOrderHelper(n->right);
        }
};