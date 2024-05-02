#pragma once
#include <iostream>
#include <string>

using std::string;

struct Node {
    string key;
    Node* parent;
    Node* left;
    Node* right;

    Node() : key(""), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(const string& str) : key(str), parent(nullptr), left(nullptr), right(nullptr) {}
    ~Node();
    // rule of three
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};