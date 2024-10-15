#include "experimentFunctions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

// Utility function to compute log2
double log2(double d) {
    return std::log(d) / std::log(2);
}

// Insert random integers into the AVL tree
void insertRandomIntegers(AVLTree<int>* avl, int numIntegers) {
    // The range of random integers
    const int minValue = -1000000000;
    const int maxValue = 1000000000;
    int randomInteger;

    // Generate a uniform distribution to generate random integers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);

    // Generate random integers (without duplicates) from the specified range
    for (int i = 0; i < numIntegers; ++i) {
        randomInteger = dist(rng);
        while (avl->contains(randomInteger)) {
            randomInteger = dist(rng);
        }
        avl->insert(randomInteger);
    }
}

// Delete random integers from the AVL tree by rank
void deleteRandomIntegers(AVLTree<int>* avl, int numDelete) {
    int treeSize = avl->treeSize();
    if (treeSize == 0) {
        std::cout << "Tree is empty, no nodes to delete." << std::endl;
        return;
    }

    // The range of random ranks
    const int minValue = 1;
    const int maxValue = treeSize;
    int randomRank;

    // Generate a uniform distribution to generate random integers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(minValue, maxValue);

    // Randomly delete a node by its rank in AVL
    for (int i = 0; i < numDelete; i++) {
        randomRank = dist(rng);
        avl->removeByRank(randomRank - 1); // Use rank - 1 since rank is 1-based in the logic
    }
}

// Experiment 1: Insert in different orders and validate AVL tree properties
void experiment1(int numIntegers) {
    AVLTree<int> tree1, tree2, tree3;

    // Insert odd numbers in ascending, descending, and random order
    std::vector<int> testValues;
    std::vector<int> testValuesReversed;
    std::vector<int> testValuesShuffled;

    for (int i = 0; i < numIntegers; i++) {
        if (i % 2 != 0) { // Odd values only
            testValues.push_back(i);
            testValuesReversed.push_back(i);
            testValuesShuffled.push_back(i);
        }
    }

    // Reverse and shuffle for different insert orders
    std::reverse(testValuesReversed.begin(), testValuesReversed.end());
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(testValuesShuffled.begin(), testValuesShuffled.end(), rng);

    // Insert in ascending order
    for (const int& value : testValues) {
        tree1.insert(value);
    }

    // Insert in descending order
    for (const int& value : testValuesReversed) {
        tree2.insert(value);
    }

    // Insert in random order
    for (const int& value : testValuesShuffled) {
        tree3.insert(value);
    }

    // Test AVL properties (isBST, isBalanced, contains) and print the results
    std::cout << "Experiment 1 - Tree 1 (Ascending Order): " << std::endl;
    std::cout << "Tree Size: " << tree1.treeSize() << ", Height: " << tree1.computeHeight() << ", Balanced: " << (tree1.isBalanced() ? "Yes" : "No") << std::endl;

    std::cout << "Experiment 1 - Tree 2 (Descending Order): " << std::endl;
    std::cout << "Tree Size: " << tree2.treeSize() << ", Height: " << tree2.computeHeight() << ", Balanced: " << (tree2.isBalanced() ? "Yes" : "No") << std::endl;

    std::cout << "Experiment 1 - Tree 3 (Random Order): " << std::endl;
    std::cout << "Tree Size: " << tree3.treeSize() << ", Height: " << tree3.computeHeight() << ", Balanced: " << (tree3.isBalanced() ? "Yes" : "No") << std::endl;
}

// Stage 1: Insert random integers into AVL tree
void stage1(AVLTree<int>* avl, int numIntegers) {
    insertRandomIntegers(avl, numIntegers);
    std::cout << "Stage 1 Complete: Tree Size = " << avl->treeSize() << ", Height = " << avl->computeHeight() << std::endl;
}

// Stage 2: Random insert/remove pair operations to test average depth invariance
void stage2(AVLTree<int>* avl, int numRandomInsertRemove) {
    for (int i = 0; i < numRandomInsertRemove; ++i) {
        insertRandomIntegers(avl, 1);
        deleteRandomIntegers(avl, 1);
    }
    std::cout << "Stage 2 Complete: Tree Size = " << avl->treeSize() << ", Height = " << avl->computeHeight() << ", Avg Depth = " << avl->averageDepth() << std::endl;
}

// Other test and utility functions can be added as needed.
