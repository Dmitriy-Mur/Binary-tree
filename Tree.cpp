#include "Tree.h"

int Tree::getData() {
    return data;
}

void Tree::setData(int data) {
    this->data = data;
}

Tree* Tree::getLeft() {
    return left;
}

void Tree::setLeft(Tree* left) {
    this->left = left;
}

Tree* Tree::getRight() {
    return right;
}

void Tree::setRight(Tree* right) {
    this->right = right;
}

Tree* Tree::getParent() {
    return parent;
}

void Tree::setParent(Tree* parent) {
    this->parent =parent;
}

Tree::Tree() {
    data = NULL;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

Tree::Tree(int data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

Tree::Tree(int data, Tree* left, Tree* right, Tree* parent) {
    this->data = data;
    this->left = left;
    this->right = right;
    this->parent = parent;
}

Tree* Tree::minTree(Tree* tree) {
    if (tree->left == nullptr) return this;
    return tree->left->minTree(tree->left);
}

Tree* Tree::maxTree(Tree* tree) {
    if (tree->right == nullptr) return this;
    return tree->right->minTree(tree->right);
}

void Tree::insert(int data) {
    Tree* temp_tree = this;
    while (temp_tree != nullptr) {
        if (data > temp_tree->data) {
            if (temp_tree->right != nullptr) {
                temp_tree = temp_tree->right;
            } else {
                Tree* tmp = new Tree(data);
                tmp->parent = temp_tree;
                temp_tree->right = tmp;
                break;
            }
        } else if (data < temp_tree->data) {
            if (temp_tree->left != nullptr) {
                temp_tree = temp_tree->left;
            } else {
                Tree* tmp = new Tree(data);
                tmp->parent = temp_tree;
                temp_tree->left = tmp;
                break;
            }
        } else {
            break;
        }
    }
}

Tree* Tree::find(int data) {
    if (this == nullptr) {
        return nullptr;
    }
    if (this->data == data) {
        return this;
    } else if (data < this->data) {
        return this->left->find(data);
    } else if (data > this->data) {
        return this->right->find(data);
    }
}

bool Tree::erase(int data){
    Tree* node = this->find(data);
    if (node == nullptr) {
        return false;
    }
    if ((node->left == nullptr) && (node->right == nullptr)) {
        Tree* node_par = node->parent;
        if (node_par->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    } else if ((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) {
        Tree* node_par = node->parent;
        if (node->left == nullptr) {
            if (node_par->left == node) {
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
            node->right->parent = node->parent;
        }
        else {
            if (node_par->left == node) {
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
            node->left->parent = node->parent;
        }
        delete node;
    }
    else {
        Tree* r_tree_min = node->right->minTree(node->right);
        if (r_tree_min->left == nullptr && r_tree_min->right == nullptr) {
            int tmp = r_tree_min->data;
            this->erase(r_tree_min->data);
            node->data = tmp;
        } else {
            int tmp = r_tree_min->data;
            this->erase(r_tree_min->data);
            node->data = tmp;
        }
    }
    return true;
}
void Tree::clear() {
    if (this == nullptr) {
        return;
    }
    this->left->clear();
    this->right->clear();
    delete this;
}

void Tree::balance() {
    std::vector<int> values;
    inorderTraversal(this, values);
    Tree* balancedTree = buildBalancedTree(values, 0, values.size() - 1);
    *this = *balancedTree;
}

void Tree::inorderTraversal(Tree* node, std::vector<int>& values){
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left, values);
    values.push_back(node->data);
    inorderTraversal(node->right, values);
}

Tree* Tree::buildBalancedTree(const std::vector<int>& values, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Tree* newNode = new Tree(values[mid]);
    newNode->left = buildBalancedTree(values, start, mid - 1);
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }
    newNode->right = buildBalancedTree(values, mid + 1, end);
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }
    return newNode;
}
