#include "../include/avl_tree.h"

using namespace std;

int main(void) {
    avl_tree *avl = new avl_tree(0);
    
    for (int i = 0; i < 10; i++) {
        avl->insert(i);
    }

    cout << "AVL tree has " << avl->getNumNodes() << " nodes" << endl;
    avl->printInOrder();

    avl->~avl_tree();

    return 0;
}