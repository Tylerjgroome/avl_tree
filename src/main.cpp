#include "../include/avl_tree.h"

using namespace std;

int main(void) {
    avl_tree *avl = new avl_tree(0);
    
    for (int i = 10; i > 0; i--) {
        avl->insert(i);
    }

    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    avl->printInOrder();
    cout << avl->findNode(3)->value << endl;
    avl->remove(4);
    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    avl->printInOrder();

    cout << "Height of AVL tree is " << avl->getRootNode()->left->left->left->height << endl;

    avl->~avl_tree();

    return 0;
}