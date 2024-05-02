#include "Node.h"

Node::~Node() {   // tears down children
    delete left;
    delete right;
}