#include "../include/avl_tree.h"

using namespace std;

int main(void) {
    
    // create pointer to AVL tree and initialise root node with value 0
    avl_tree *avl = new avl_tree(0);
    
    for (int i = 10; i > 0; i--) {
        // insert integers 10 through to 1
        avl->insert(i);
    }

    // print the number of nodes in the tree (expect 11)
    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;

    // print tree in order (expect 0,1,2,3,4,5,6,7,8,9,10)
    avl->printInOrder();

    // print the height of the AVL tree (expect 4)
    cout << "Height of AVL tree is " << avl->getMaxHeight() << endl;

    // remove value 9 from the tree
    avl->remove(9);

    // print the number of nodes in the tree (expect 10)
    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    
    // print the tree in order (expect 0,1,2,3,4,5,6,7,8,10)
    avl->printInOrder();

    // print the height of the tree (expect 4)
    cout << "Height of AVL tree is " << avl->getMaxHeight() << endl;

    // delete allocated memory for the tree and its nodes from the heap
    avl->~avl_tree();

    return 0;
}