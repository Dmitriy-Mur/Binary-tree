#pragma once
#include <vector>

class Tree {
public:
    int data;
    Tree* left;
    Tree* right;
    Tree* parent;
public:
    int getData();
    void setData(int data);
    Tree* getLeft();
    void setLeft(Tree* left);
    Tree* getRight();
    void setRight(Tree* right);
    Tree* getParent();
    void setParent(Tree* parent);
    Tree();
    Tree(int data);
    Tree(int data, Tree* left, Tree* right, Tree* parent);
    Tree* minTree(Tree* tree);
    Tree* maxTree(Tree* tree);
    void insert(int data);
    Tree* find(int data);
    bool erase(int data);
    void clear();
    void balance();
    void inorderTraversal(Tree* node, std::vector<int>& values);
    Tree* buildBalancedTree(const std::vector<int>& values, int start, int end);
};
