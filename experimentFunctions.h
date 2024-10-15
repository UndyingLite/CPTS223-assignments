#ifndef EXPERIMENT_FUNCTIONS_H
#define EXPERIMENT_FUNCTIONS_H

#include "AVLTree.h"

// Function prototypes for experiments
void experiment1(int numIntegers);
void stage1(AVLTree<int>* avl, int numIntegers);
void stage2(AVLTree<int>* avl, int numRandomInsertRemove);

bool testBST(AVLTree<int>* avl);
bool testBalanced(AVLTree<int>* avl);
bool testContains(AVLTree<int>* avl, int numIntegers);
bool testSize(AVLTree<int>* avl, int targetNumIntegers);
bool testHeight(AVLTree<int>* avl);

void insertRandomIntegers(AVLTree<int>* avl, int numIntegers);
void deleteRandomIntegers(AVLTree<int>* avl, int numDelete);

#endif // EXPERIMENT_FUNCTIONS_H
