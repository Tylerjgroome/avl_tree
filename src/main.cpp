#include "../include/avl_tree.h"

using namespace std;

int main(void) {
    avl_tree *avl = new avl_tree(0);
    
    for (int i = 1; i < 2; i++) {
        avl->insert(i);
    }

    std::cout << avl->getNumNodes() << std::endl;

    avl->~avl_tree();

    return 0;
}