#pragma once
#include "Tree.h"

class BinaryTree {
public:
    Tree* root;
public:
    void setRoot(Tree* root);
    Tree* getRoot();
    BinaryTree();
    BinaryTree(int data);
    void insert(int data);
    Tree* find(int data);
    bool erase(int data);
    void balance();
    void clear();
};
