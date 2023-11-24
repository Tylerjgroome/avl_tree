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
        node *getRootNode(void);
        void setRootNode(node *n);
        int getMaxHeight(void);
        void setMaxHeight(int height);
        int getNumNodes(void);
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

        node *rightRotation(node * n) {
            node *left = n->left;
            node *right_left = left->right;

            left->right = n;
            n->left = right_left;

            n->height = 1 + max(getHeight(n->left),getHeight(n->right));
            left->height = 1 + max(getHeight(left->left),getHeight(left->right));

            root = left;

            return left;
        }

        node *leftRotation(node * n) {
            node *right = n->right;
            node *left_right = right->left;

            right->left = n;
            n->right = left_right;

            n->height = 1 + max(getHeight(n->left),getHeight(n->right));
            right->height = 1 + max(getHeight(right->left),getHeight(right->right));

            root = right;

            return right;
        }

        node *insertHelper(node* n, int value) {
    
            if (n == NULL) {
                return createNode(value);
            }

            if (n->value < value) {
                n->right = insertHelper(n->right,value);
            } else if (n->value > value) {
                n->left = insertHelper(n->left,value);
            } else {
                // no duplicates
                std::cout << "Duplicate value ignored" << std::endl;
                return NULL;
            }

            int height = max(getHeight(n->left),getHeight(n->right));

            n->height = height++;

            int balance_factor = getBalance(n);

            if (balance_factor > 1 && n->left->value > value) rightRotation(n);
            if (balance_factor < -1 && n->right->value < value) leftRotation(n);

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
};