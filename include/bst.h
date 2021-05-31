// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include  <iostream>
#include  <fstream>

bool is_char(char data) {
    std::string alf = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    bool alf_sym = 0;
    for (int i = 0; i < alf.size(); i++) {
        if (data == alf[i]) {
            alf_sym = 1;
            break;
        }
    }
    return alf_sym;
}

template <typename T>
class BST {
     public:
    BST() : root(nullptr) {}
    ~BST();
    void add(T);
    void print();
    int depth();
    int search(T);
    bool is_empty() { return root == nullptr; }
    void buildTreeFromFile(const char *filename);
    class Node {
     public:
        T data;
        class Node* left;
        class Node* right;
        int count;
     private:
    };
     private:
    Node* root;

    Node* addNode(Node* root, T value);
    void printTree(Node* root);
    void delTree(Node* root);
    int getHeight(Node* root);
    int searchNode(Node* root, T value);
};

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
    if (root == nullptr) {
        root = new Node;
        root->data = value;
        root->count = 1;
        root->left = nullptr;
        root->right = nullptr;
    } else if (root->data > value) {
        root->left = addNode(root->left, value);
    } else if (root->data < value) {
        root->right = addNode(root->right, value);
    } else {
        root->count++;
    }
    return root;
}

template<typename T>
void BST<T>::printTree(Node* root) {
    if (is_empty()) return;
    printTree(root->left);
    for (int i = 0; i < root->count; i++)
        std::cout << root->data << " ";
    printTree(root->right);
}

template<typename T>
void BST<T>::delTree(Node* root) {
    if (root == nullptr) {
        return; 
    } else {
        delTree(root->left);
        delTree(root->right);
        delete root;
    }
}

template<typename T>
int BST<T>::getHeight(Node* root) {
    if (root == nullptr) return 0;
    //must have, cuz counting always + 1 (if lh = rh = 0 then error)
    if (root->left == nullptr && root->right == nullptr) return 0;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

template<typename T>
int BST<T>::searchNode(Node* root, T value) {
    if (root == nullptr) return 0;
    else if (root->data == value) return root->count;
    else if (root->data > value) return searchNode(root->left, value);
    else return searchNode(root->right, value);
}

template<typename T>
BST<T>::~BST() {
    //отключен из-за проблем с методом makeTree
    //if (!(is_empty())) delTree(root);
}

template<typename T>
void BST<T>::add(T value) {
    root = addNode(root, value);
}

template<typename T>
void BST<T>::print() {
    printTree(root);
}

template<typename T>
int BST<T>::depth() {
    return getHeight(root);
}

template<typename T>
int BST<T>::search(T value) {
    return searchNode(root, value);
}

template<typename T>
void BST<T>::buildTreeFromFile(const char* filename) {
    std::string temp = filename;
    std::ifstream file(temp);
    // если файл не открылся, прекращаем работу
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    int count = 0;
    // читаем содержимое файла по слову
    while (!file.eof()) {
        std::string str = "";
        char ch = file.get();
        while (is_char(ch)) {
            str += tolower(ch);
            ch = file.get();
        }
        if (!str.empty()) {
            add(str);
        }
    }
    // закрываем файл
    file.close();
}
#endif  // INCLUDE_BST_H_
