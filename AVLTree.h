#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { root = deleteTree(root); }

    bool contains(const T& value) const { return contains(root, value); }
    void insert(const T& value) { root = insert(root, value); }
    void remove(const T& value) { root = remove(root, value); }
    void removeByRank(int rank) { root = removeByRank(root, rank); }
    int treeSize() const { return treeSize(root); }
    int computeHeight() const { return computeHeight(root); }
    double averageDepth() const { return (treeSize() == 0) ? 0 : (double)sumDepth(root, 0) / treeSize(); }
    bool isBST() const { return isBST(root, nullptr, nullptr); }
    bool isBalanced() const { return isBalanced(root); }
    int readRootHeight() const { return root ? root->height : -1; }

private:
    AVLNode<T>* root;

    AVLNode<T>* deleteTree(AVLNode<T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
        return nullptr;
    }

    int height(AVLNode<T>* node) const { return node ? node->height : 0; }

    int balanceFactor(AVLNode<T>* node) const {
        return height(node->left) - height(node->right);
    }

    AVLNode<T>* rotateWithLeftChild(AVLNode<T>* k2) {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        return k1;
    }

    AVLNode<T>* rotateWithRightChild(AVLNode<T>* k1) {
        AVLNode<T>* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k2->height = std::max(height(k2->right), k1->height) + 1;
        return k2;
    }

    AVLNode<T>* doubleWithLeftChild(AVLNode<T>* k3) {
        k3->left = rotateWithRightChild(k3->left);
        return rotateWithLeftChild(k3);
    }

    AVLNode<T>* doubleWithRightChild(AVLNode<T>* k1) {
        k1->right = rotateWithLeftChild(k1->right);
        return rotateWithRightChild(k1);
    }

    AVLNode<T>* balance(AVLNode<T>* node) {
        if (!node) return node;

        if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) >= 0)
                node = rotateWithLeftChild(node);
            else
                node = doubleWithLeftChild(node);
        } else if (balanceFactor(node) < -1) {
            if (balanceFactor(node->right) <= 0)
                node = rotateWithRightChild(node);
            else
                node = doubleWithRightChild(node);
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
        return node;
    }

    AVLNode<T>* insert(AVLNode<T>* node, const T& value) {
        if (!node) return new AVLNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node; // No duplicates allowed

        return balance(node);
    }

    AVLNode<T>* remove(AVLNode<T>* node, const T& value) {
        if (!node) return node;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                AVLNode<T>* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node) return node;

        return balance(node);
    }

    AVLNode<T>* removeByRank(AVLNode<T>* node, int rank) {
        if (!node) return nullptr;

        int leftSize = treeSize(node->left);
        if (rank < leftSize)
            node->left = removeByRank(node->left, rank);
        else if (rank > leftSize)
            node->right = removeByRank(node->right, rank - leftSize - 1);
        else {
            return remove(node, node->data);
        }

        return balance(node);
    }

    AVLNode<T>* findMin(AVLNode<T>* node) const {
        while (node->left) node = node->left;
        return node;
    }

    bool contains(AVLNode<T>* node, const T& value) const {
        if (!node) return false;
        if (value < node->data)
            return contains(node->left, value);
        else if (value > node->data)
            return contains(node->right, value);
        else
            return true;
    }

    int treeSize(AVLNode<T>* node) const {
        if (!node) return 0;
        return 1 + treeSize(node->left) + treeSize(node->right);
    }

    int computeHeight(AVLNode<T>* node) const {
        if (!node) return -1;
        return 1 + std::max(computeHeight(node->left), computeHeight(node->right));
    }

    int sumDepth(AVLNode<T>* node, int depth) const {
        if (!node) return 0;
        return depth + sumDepth(node->left, depth + 1) + sumDepth(node->right, depth + 1);
    }

    bool isBST(AVLNode<T>* node, AVLNode<T>* minNode, AVLNode<T>* maxNode) const {
        if (!node) return true;
        if ((minNode && node->data <= minNode->data) || (maxNode && node->data >= maxNode->data))
            return false;
        return isBST(node->left, minNode, node) && isBST(node->right, node, maxNode);
    }

    bool isBalanced(AVLNode<T>* node) const {
        if (!node) return true;
        int balance = balanceFactor(node);
        return std::abs(balance) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }
};

#endif // AVLTREE_H
