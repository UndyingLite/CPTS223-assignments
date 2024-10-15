#include "AVLTree.h"
#include "experimentFunctions.h"
#include <iostream>

int main() {
    // Experiment 1: Test AVL tree insertion in different orders
    std::cout << "================================ Experiment 1 =================================" << std::endl;
    experiment1(20);
    std::cout << std::endl;

    // Experiment 2: Test whether average depth of AVL trees is invariant to random insert/remove pair operations
    std::cout << "============================ Experiment 2, Stage 1 ============================" << std::endl;
    AVLTree<int>* avl = new AVLTree<int>();
    stage1(avl, 20);
    std::cout << std::endl;

    // Stage 2: Perform 500^2 random insert/delete pairs
    int numRandomInsertRemove = 250000;
    std::cout << "========== Experiment 2, Stage 2 (after " << numRandomInsertRemove << " random insert/delete) ==========" << std::endl;
    stage2(avl, numRandomInsertRemove);

    delete avl;
    return 0;
}
