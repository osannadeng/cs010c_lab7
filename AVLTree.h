#pragma once
#include <iostream>
#include <string>

#include "Node.h"

// only implementing what is used
using std::string;
using std::cout;
using std::endl;
using std::abs;

class AVLTree {
 private:   // member variables
    Node* root;
 public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { delete root; }

    // rule of three
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    void insert(const string&);
    int balanceFactor(const Node*) const;
    void printBalanceFactors() const;
 private:   // helper functions
    Node* findUnbalancedNode(Node*) const;
    Node* rotate(Node*);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    void printBalanceFactors(const Node*) const;
    int height(const Node*) const;
};