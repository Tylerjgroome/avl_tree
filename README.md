# avl_tree
C++ implementation of an AVL (self-rotating) tree for $O(log(n))$ search time complexity.

Adapted from [Geeks for Geeks](https://www.geeksforgeeks.org/introduction-to-avl-tree/?ref=lbp) implementation.

An AVL tree is a variant of a binary search tree (BST) that has the ability to self-rotate its arrangement to minimise its height at all times. This allows for a reduced time complexity of $O(log(n))$ to be achieved when searching the tree rather than a worst-case $O(n)$. 

BST's are data structures consisting of nodesc containing values. The arrangement of the nodes in the tree is such that all nodes to the left of a parent node are smaller in value, and all nodes to the right of a parent value are larger in value, as shown in the image below. The order of the nodes in the tree is dependent on the order in which they are inserted into the tree
![avl](https://github.com/Tylerjgroome/avl_tree/assets/110513531/1e59c559-6acf-4469-bcba-50a31223f2ff)

An AVL tree conserves this behaviour but self-rotates when nodes are added or removed to minimise its height for reduces searching time complexity. To achieve this, each node has an associated height, where nodes at the bottom of the tree have height 1 and the root node at the top of the tree has the maximum height which represents the overall height of the tree.
![avl2](https://github.com/Tylerjgroome/avl_tree/assets/110513531/f3a2594f-04c0-47c8-be9c-91d500e21223)

A balance factor is calculated for each node when inserting or removing a value from the tree, this factor represents the difference between the high of a nodes left sub-tree and its right-subtree. When this value exceeds 1 in magnitude, a rotation is required.
![avl3](https://github.com/Tylerjgroome/avl_tree/assets/110513531/11d91241-6304-457c-9019-e3c26ef8d775)

Adding a node with value 80 causes the node with value 59 to become unbalanced, this nessecitates a left rotation.
![avl4](https://github.com/Tylerjgroome/avl_tree/assets/110513531/cd609c90-6514-470e-bb1a-f4feadec8c02)

After the left rotation, the tree becomes balanced:
![avl5](https://github.com/Tylerjgroome/avl_tree/assets/110513531/c4f34aa7-3447-4ec9-b026-9f6471035cd4)

To compile the code using g++ run the following command:

`g++ main.cpp avl_tree.cpp -o main.exe`

Run the main.cpp driver script (in the avl_tree/src directory) using:

`./main.exe`
