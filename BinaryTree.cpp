#include "BinaryTree.h"
#include "Tree.h"

void BinaryTree::setRoot(Tree* root) {
    this->root = root;
}

Tree* BinaryTree::getRoot() {
    return root;
}

BinaryTree::BinaryTree() {
    root = nullptr;
}

BinaryTree::BinaryTree(int data) {
    root = new Tree(data, nullptr, nullptr, nullptr);
}

void BinaryTree::insert(int data) {
    this->root->insert(data);
}

Tree* BinaryTree::find(int data) {
    return (this->root->find(data));
}

bool BinaryTree::erase(int data) {
    return (this->root->erase(data));
}

void BinaryTree::balance() {
    if(this->root != nullptr)
        this->root->balance();
}

void BinaryTree::clear() {
    this->root->clear();
    this->root = nullptr;
}
