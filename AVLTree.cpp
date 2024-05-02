#include "AVLTree.h"

// insert item to binary search tree while keeping tree balanced
void AVLTree::insert(const string& key) {
    // node is empty
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    Node* curr = root;
    while (curr) {
        // already in tree
        if (key == curr->key) return;
        // move to left branch
        if (key < curr->key) {
            // found hole (no child)
            if (curr->left == nullptr) {
                curr->left = new Node(key);
                curr->left->parent = curr;
                break;
            } else {
                curr = curr->left;
            }
        } else {    // move to right branch
            // found hole
            if (curr->right == nullptr) {
                curr->right = new Node(key);
                curr->right->parent = curr;
                break;
            } else {
                curr = curr->right;
            }
        }
    }
    // rebalance if unbalanced
    // loops until balanced
    curr = findUnbalancedNode(curr);
    while (curr) {
        curr = rotate(curr);
        curr = findUnbalancedNode(curr);
    }
}

// return balance factor of given node
int AVLTree::balanceFactor(const Node* curr) const {
    if (!curr) return 0;
    // left subtree height - right subtree height
    return height(curr->left) - height(curr->right);
}

// traverse and print tree in inorder notation
void AVLTree::printBalanceFactors() const {
    if (!root) return;    // empty
    printBalanceFactors(root);  // helper
    cout << endl;
}

// helper, find and return closest unbalanced node (balance factor of 2 or -2) to inserted node
// traverses from bottom up
Node* AVLTree::findUnbalancedNode(Node* curr) const {
    // no node is unbalanced
    if (!curr) return nullptr;
    if (abs(balanceFactor(curr)) == 2) return curr;
    return findUnbalancedNode(curr->parent);
}

// helper, implement four possible imbalance cases, update parent
Node* AVLTree::rotate(Node* curr) {
    // right heavy
    if (balanceFactor(curr) == -2) {
        // double rotation
        if (balanceFactor(curr->right) == 1) {
            rotateRight(curr->right);
        }
        return rotateLeft(curr);
    }
    // left heavy
    if (balanceFactor(curr) == 2) {
        // double rotation
        if (balanceFactor(curr->left) == -1) {
            rotateLeft(curr->left);
        }
        return rotateRight(curr);
    }
    return curr;
}

// helper, rotate subtree to left at node, return new subroot
Node* AVLTree::rotateLeft(Node* curr) {
    // root case
    if (curr == root) {
        root = curr->right;
        root->parent = nullptr;
        curr->right = root->left;
        root->left = curr;
        curr->parent = root;
        return root;
    }
    Node* child = curr->right;
    child->parent = curr->parent;
    // if curr is left child
    if (curr == curr->parent->left) curr->parent->left = child;
    // if curr is right child
    else curr->parent->right = child;
    curr->right = child->left;
    child->left = curr;
    curr->parent = child;
    return child;
}

// helper, rotate subtree to right at node, return new subroot
Node* AVLTree::rotateRight(Node* curr) {
    // root case
    if (curr == root) {
        root = curr->left;
        root->parent = nullptr;
        curr->left = root->right;
        root->right = curr;
        curr->parent = root;
        return root;
    }
    Node* child = curr->left;
    child->parent = curr->parent;
    // if curr is left child
    if (curr == curr->parent->left) curr->parent->left = child;
    // if curr is right child
    else curr->parent->right = child;
    curr->left = child->right;
    child->right = curr;
    curr->parent = child;
    return child;
}

// helper, traverse and print tree in inorder notation starting at node
void AVLTree::printBalanceFactors(const Node* curr) const {
    // print string, balance factor in parentheses, comma, space
    if(!curr) return;
    printBalanceFactors(curr->left);
    cout << curr->key << "(" << balanceFactor(curr) << "), ";
    printBalanceFactors(curr->right);    
}

// helper, returns largest height from left and right subtrees + 1
int AVLTree::height(const Node* curr) const {
    // bottom or not found
    if (!curr) return -1;
    int countLeft = height(curr->left);
    int countRight = height(curr->right);
    if (countLeft > countRight) return countLeft + 1;
    return countRight + 1;
}