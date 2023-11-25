#include "../include/avl_tree.h"

using namespace std;

int main(void) {
    avl_tree *avl = new avl_tree(0);
    
    for (int i = 10; i > 0; i--) {
        avl->insert(i);
    }

    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    avl->printInOrder();

    cout << "AVL tree root value: " << endl;

    avl->remove(4);
    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    avl->printInOrder();

    cout << "Height of AVL tree is " << avl->getMaxHeight() << endl;

    avl->~avl_tree();

    return 0;
}