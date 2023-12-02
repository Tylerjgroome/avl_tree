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

// set the root node of the tree
void avl_tree::setRootNode(node *n) {
    root = n;
}

// create a new node with value
node *avl_tree::createNode(int value) {
    node *new_node = new node;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1; // added to bottom of tree
    
    return new_node;
}

// function to get the height of a node, if it exists
int avl_tree::getHeight(node *n) {
    if (n == NULL) {
        return 0;
    }

    return n->height;
}

// function to get the balance factor of a node, if it exists
int avl_tree::getBalance(node* n) {
    if (n == NULL) {
        return 0;
    }

    return getHeight(n->left) - getHeight(n->right);
}

// convenience function to return the maximum of integers a and b
int avl_tree::max(int a, int b) {
    return (a > b) ? a : b;
}

// right rotation function
node *avl_tree::rightRotation(node * y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left),getHeight(y->right));
    x->height = 1 + max(getHeight(x->left),getHeight(x->right));

    return x;
}

// left rotation function
node *avl_tree::leftRotation(node * x) {
    node *y = x->right;
    node *T2 = y->left;
    
    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left),getHeight(x->right));
    y->height = 1 + max(getHeight(y->left),getHeight(y->right));
    
    return y;
}

// function to update the height of the tree
void avl_tree::updateMaxHeight() {
    max_height = getRootNode()->height;
}

// recursive insert function helper
node *avl_tree::insertHelper(node* n, int value) {

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
node * avl_tree::minValueNode(node * n) {
    node *curr = n;

    while (curr->left != NULL) {
        curr = curr->left;
    }

    return curr;
}

// insert value into the AVL tree and self-balance
void avl_tree::insert(int value) {
    node *n = insertHelper(root,value);
    setRootNode(n);
    num_nodes++;
    updateMaxHeight();
    return;
}

// recursive remove helper function
node *avl_tree::removeHelper(node* n, int value) {

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

// remove value from the AVL tree and self-balance
void avl_tree::remove(int value) {
    node *n = removeHelper(root,value);
    
    if (n != NULL) {
        setRootNode(n);
        num_nodes--;
    } else {
        std::cout << "Value " << value << " not found in AVL tree" << std::endl;
    }
    updateMaxHeight();
    return;
}

// function to recursively delete all nodes in the AVL tree (on ~AVL_tree() call)
node *avl_tree::deleteNodes(node *n) {
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
void avl_tree::printInOrderHelper(node *n) {
    if (n == NULL) {
        return;
    }

    printInOrderHelper(n->left);
    
    std::cout << n->value << " ";

    printInOrderHelper(n->right);
}

// helper function for print post order
void avl_tree::printPostOrderHelper(node *n) {
    if (n == NULL) {
        return;
    }

    printPostOrderHelper(n->left);

    printPostOrderHelper(n->right);

    std::cout << n->value << " ";
}

// helper function for print pre order
void avl_tree::printPreOrderHelper(node *n) {
    if (n == NULL) {
        return;
    }
    
    std::cout << n->value << " ";

    printPreOrderHelper(n->left);

    printPreOrderHelper(n->right);
}

// get the root node of the tree
node * avl_tree::getRootNode(void) {
    return root;
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

// check whether a value exists in the tree
bool avl_tree::check(int value) {
    node *n = root;

    while (n != NULL) {
        if (n->value > value) {
            n = n->left;
        } else if (n->value < value) {
            n = n->right;
        } else {
            // value found
            return true;
        }
    }

    // value not found if this point is reached
    return false;
}

// function to find a node with particular value in the tree
node * avl_tree::findNode(int value) {
    if (check(value)) {
        node *n = root;

        while (n != NULL) {
            if (n->value > value) {
                n = n->left;
            } else if (n->value < value) {
                n = n->right;
            } else {
                // node found
                return n;
            }
        }
    } else {
        // node not found
        return NULL;
    }
}

// AVL tree destructor, calls recursive private deleteNodes method
avl_tree::~avl_tree() {
    deleteNodes(root);
}