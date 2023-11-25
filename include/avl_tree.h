#pragma once
#include <iostream>

struct node {
    int value;
    int balance;
    int height;
    node *left;
    node *right;
};

class avl_tree {
    public:
        avl_tree(void);
        avl_tree(int value);
        void insert(int value);
        void remove(int value);
        node *getRootNode(void);
        void setRootNode(node *n);
        int getMaxHeight(void);
        int getNumNodes(void);
        void printInOrder(void);
        void printPreOrder(void);
        void printPostOrder(void);
        bool check(int value);
        node* findNode(int value);
        ~avl_tree();
    private:
        int num_nodes;
        int max_height;
        node *root;

        node *createNode(int value) {
            node *new_node = new node;
            new_node->value = value;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->height = 1;
            
            return new_node;
        }

        int getHeight(node *n) {
            if (n == NULL) {
                return 0;
            }

            return n->height;
        }

        int getBalance(node* n) {
            if (n == NULL) {
                return 0;
            }

            return getHeight(n->left) - getHeight(n->right);
        }

        int max(int a, int b) {
            return (a > b) ? a : b;
        }

        node *rightRotation(node * y) {
            node *x = y->left;
            node *T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = 1 + max(getHeight(y->left),getHeight(y->right));
            x->height = 1 + max(getHeight(x->left),getHeight(x->right));

            return x;
        }

        node *leftRotation(node * x) {
            node *y = x->right;
            node *T2 = y->left;
            
            y->left = x;
            x->right = T2;

            x->height = 1 + max(getHeight(x->left),getHeight(x->right));
            y->height = 1 + max(getHeight(y->left),getHeight(y->right));
            
            return y;
        }

        void updateMaxHeight() {
            max_height = getRootNode()->height;
        }

        node *insertHelper(node* n, int value) {
    
            if (n == NULL) {
                node *n = createNode(value);
                if (root == NULL) {
                    root = n;
                }
                return n;
            }

            if (n->value < value) {
                n->right = insertHelper(n->right,value);
            } else if (n->value > value) {
                n->left = insertHelper(n->left,value);
            } else {
                // no duplicates
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

        node *removeHelper(node* n, int value) {
    
            if (n == NULL) {
                return createNode(value);
            }

            if (n->value < value) {
                n->right = removeHelper(n->right,value);
            } else if (n->value > value) {
                n->left = removeHelper(n->left,value);
            } else {
                // value found
                node *copy = n->right;
                delete n;
                return copy;
            }

            int height = max(getHeight(n->left),getHeight(n->right));

            n->height = height++;

            int balance_factor = getBalance(n);

            if (balance_factor > 1 && n->left->value > value) return rightRotation(n);
            if (balance_factor < -1 && n->right->value < value) return leftRotation(n);

            if (balance_factor > 1 && n->left->value < value) {
                n->left = leftRotation(n->left);
                return rightRotation(n);
            }

            if (balance_factor < -1 && n->right->value > value) {
                n->right = rightRotation(n->right);
                return leftRotation(n);
            }

            return n;
        };

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

        void printInOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }

            printInOrderHelper(n->left);
            
            std::cout << n->value << " ";

            printInOrderHelper(n->right);
        }

        void printPostOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }

            printPostOrderHelper(n->left);

            printPostOrderHelper(n->right);

            std::cout << n->value << " ";
        }

        void printPreOrderHelper(node *n) {
            if (n == NULL) {
                return;
            }
            
            std::cout << n->value << " ";

            printPreOrderHelper(n->left);

            printPreOrderHelper(n->right);
        }
};