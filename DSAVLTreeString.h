//
// Created by Saaketh Koka on 4/14/21.
//

#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "DSAVLTreeNode.h"
#include <cstring>
#include <vector>
#include <fstream>
template<class T>
class DSAVLTree<std::string, T>{
private:
    DSAVLTreeNode<std::string,T> *root;

    // Or we can caluclate the number of nodes when we want to output the stats (easier):

    inline void insert(const std::string& key, const T &value, DSAVLTreeNode<std::string,T> *&t);
    inline void balance(DSAVLTreeNode<std::string,T> *&t);


    //contains helper
    inline bool contains(const std::string& key, DSAVLTreeNode<std::string,T>*& node) const;

    inline T *get(const std::string& key, DSAVLTreeNode<std::string,T>*& node);

    //print methods
    void printPreOrder(const DSAVLTreeNode<std::string,T>* node) const;
    void printInOrder(const DSAVLTreeNode<std::string,T>* node) const;
    void printPostOrder(const DSAVLTreeNode<std::string,T>* node) const;

    // Rotation Methods:
    inline void rotateWithLeftChild(DSAVLTreeNode<std::string,T>*& node);
    inline void rotateWithRightChild(DSAVLTreeNode<std::string,T>*& node);
    inline void doubleWithLeftChild(DSAVLTreeNode<std::string,T>*& node);
    inline void doubleWithRightChild(DSAVLTreeNode<std::string,T>*& node);

    // Get Height of node:
    int getHeight(DSAVLTreeNode<std::string,T> *&node);

    // Clone
    DSAVLTreeNode<std::string,T>* clone(DSAVLTreeNode<std::string,T>*& node);

    //destructor helper
    void destructorHelper(DSAVLTreeNode<std::string,T>*& node);

    void getVectOfElementsHelper(const DSAVLTreeNode<std::string,T>* node, std::vector<DSAVLTreeNode<std::string, T>> &vect);

    void printFileHelper(std::fstream &outfs, const DSAVLTreeNode<std::string, T> *node);


public:

    /**
     * root node constructor (and default) - Generates deep copy of tree with root root.
     * @param root - root node of tree which is being copied (by default nullptr representing empty tree)
     */
    DSAVLTree(DSAVLTreeNode<std::string,T>* root = nullptr);

    /**
     * Copy Constructor - generates the deep copy of the tree inputed
     * @param otherTree - tree which is being copied
     */
    DSAVLTree(DSAVLTree& otherTree);

    /**
     * Destructor - recursivly calls destrucotor of all subtrees
     */
    ~DSAVLTree();

    /**
     * Inserts a key value pair into the tree at the proper location and then balances the tree.
     * @param key
     * @param value
     */
    void insert(const std::string& key, const T& value);

    /**
     * Inserts an AVLTree Node into the Tree and then balance's it.
     * @param DSAVLTreeNode
     */
    void insert(const DSAVLTreeNode<std::string,T>*& node);

    /**
     * Output's whether or not a certain key is found in the tree.
     * @param key
     * @return bool
     */
    bool contains(const std::string& key) const;

    /**
     * returns the value of the node with key of key in tree
     * @param key
     * @return T - the value of node with key of key
     */
    T *get(const std::string& key);

    /**
     * Assignment Operator
     * @param tree to be copied
     * @return DSAVLTree
     */
    DSAVLTree<std::string,T>& operator=(DSAVLTree<std::string,T>& other); //overloaded assignment operator

    /**
     * Outputs the tree by printing each node the first time it is visited.
     */
    void printPreOrder() const;

    /**
     * Outputs the tree by printing each node in order.
     */
    void printInOrder() const;

    /**
     * Outputs the tree by printing each node after all children were visited.
     */
    void printPostOrder() const;

    /**
     * Returns a pointer to the root of the tree.
     * @return DSAVLTreeNode *
     */
    DSAVLTreeNode<std::string,T>* get_root() const;

    /**
     * Returns the number of unique elements in AVLTree
     * @return int representing number of nodes in the AVL Tree
     */
    std::vector<DSAVLTreeNode<std::string,T>> getVectOfElements();

    /**
     * Generates a file persistence file with all of the keys and value pairs in the tree printed in order
     * @param filename - filename of the file being generated
     */
    void printTreeToFile(std::string filename);
};




template<class T>
DSAVLTree<std::string, T>::DSAVLTree(DSAVLTreeNode<std::string, T> *targetNode) {
    if(targetNode == nullptr){
        root = nullptr;
        return;
    }
    this->root = clone(targetNode);
}


template<class T>
DSAVLTree<std::string, T>::DSAVLTree(DSAVLTree &otherTree) {
    if(otherTree.root == nullptr){
        root = nullptr;
        return;
    }
    this->root = clone(otherTree.root);
}


template<class T>
DSAVLTree<std::string, T>::~DSAVLTree() {
    destructorHelper(root);
}

template<class T>
DSAVLTree<std::string, T>& DSAVLTree<std::string, T>::operator=(DSAVLTree<std::string, T>& other) {
    if(this == &other){ //Checks to see if self = self
        return *this;
    }
    if(this->root != nullptr){
        this->~DSAVLTree<std::string,T>(); //deletes data
    }
    if(other->root == nullptr){
        this->root = nullptr; //makes root nullptr is other tree has no data
    }
    else {
        this->root = clone(other.root);
    }

    return *this;
}

template<class T>
inline void DSAVLTree<std::string, T>::insert(const std::string& key, const T& value, DSAVLTreeNode<std::string, T> *&t) {
    if(t == nullptr){
        t = new DSAVLTreeNode<std::string,T>(key,value); // Once it finds an empty node it creates a new node there.
    }
    else if(t->key < key){
        insert(key, value, t->right); // Recursively searches for proper place to insert value.
    }
    else if(key < t->key){
        insert(key, value, t->left);
    }
    balance(t);
}


template<class T>
inline void DSAVLTree<std::string, T>::balance(DSAVLTreeNode<std::string, T> *&t) {
    if(getHeight(t->left) - getHeight(t->right) > 1){
        if(getHeight(t->left->left) >= getHeight(t->left->right)){
            rotateWithLeftChild(t);
        }
        else{
            doubleWithLeftChild(t);
        }
    }
    else if(getHeight(t->right) - getHeight(t->left) > 1){
        if(getHeight(t->right->left) >= getHeight(t->right->right)){
            doubleWithRightChild(t);

        }
        else{
            rotateWithRightChild(t);
        }
    }
    t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1; // Updates height
}

template<class T>
void DSAVLTree<std::string, T>::printPreOrder() const{
    printPreOrder(root);
}

template<class T>
void DSAVLTree<std::string, T>::printPreOrder(const DSAVLTreeNode<std::string, T>* node) const{
    if(node == nullptr){
        return;
    }
    std::cout << node->key << ": " << node->value << std::endl;
    printPreOrder(node->left);
    printPreOrder(node->right);
}

template<class T>
void DSAVLTree<std::string,T>::printInOrder() const{
    printInOrder(root);
}

template<class T>
void DSAVLTree<std::string, T>::printInOrder(const DSAVLTreeNode<std::string, T>* node) const{
    if(node == nullptr){
        return;
    }
    printInOrder(node->left);
    std::cout << node->key << ": " << std::endl;
    printInOrder(node->right);
}

template<class T>
void DSAVLTree<std::string, T>::printPostOrder() const {
    printPostOrder(root);
}

template<class T>
void DSAVLTree<std::string, T>::printPostOrder(const DSAVLTreeNode<std::string, T>* node) const {
    if(node == nullptr){
        return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    std::cout << node->key << ": " << node->value << std::endl;
}


template<class T>
void DSAVLTree<std::string, T>::insert(const std::string& key, const T& value) {
    insert(key, value, root);
}

template<class T>
void DSAVLTree<std::string, T>::insert(const DSAVLTreeNode<std::string, T> *&node) {
    insert(node->key, node->value, root);
}

template<class T>
int DSAVLTree<std::string, T>::getHeight(DSAVLTreeNode<std::string, T> *&node) {
    if(node == nullptr){
        return -1;
    }
    else{
        return node->height;
    }
}

template<class T>
inline void DSAVLTree<std::string, T>::rotateWithLeftChild(DSAVLTreeNode<std::string, T>*& node) {
    DSAVLTreeNode<std::string,T> *leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    leftNode->height = std::max(getHeight(leftNode->left), node->height) + 1;
    node = leftNode;
}

template<class T>
inline void DSAVLTree<std::string, T>::rotateWithRightChild(DSAVLTreeNode<std::string, T> *&node) {
    DSAVLTreeNode<std::string,T> *rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    rightNode->height = std::max(getHeight(rightNode->right), node->height) + 1;
    node = rightNode;
}

template<class T>
inline void DSAVLTree<std::string, T>::doubleWithLeftChild(DSAVLTreeNode<std::string, T> *&node) {
    rotateWithRightChild(node->left);
    rotateWithLeftChild(node);
}

template<class T>
inline void DSAVLTree<std::string, T>::doubleWithRightChild(DSAVLTreeNode<std::string, T> *&node) {
    rotateWithLeftChild(node->right);
    rotateWithRightChild(node);
}


template<class T>
inline bool DSAVLTree<std::string, T>::contains(const std::string& key, DSAVLTreeNode<std::string, T> *&node) const {
    if(node == nullptr){
        return false;
    }
    int strCMPVal = node->key.compare(key);
//    std::cout << strCMPVal << std::endl;
    if(strCMPVal == 0){
        return true;
    }
    if(strCMPVal < 0){
        return contains(key, node->right);
    }
    else{
        return contains(key, node->left);
    }
}

template<class T>
bool DSAVLTree<std::string, T>::contains(const std::string& key) const{
    if(this->root == nullptr){
        return false;
    }
    if(this->root->key == key){
        return true;
    }
    DSAVLTreeNode<std::string,T> *node = root;
    return contains(key, node);
}

template<class T>
void DSAVLTree<std::string, T>::destructorHelper(DSAVLTreeNode<std::string, T> *&node) {
    if(node == nullptr){
        return;
    }
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}

template<class T>
DSAVLTreeNode<std::string, T> *DSAVLTree<std::string, T>::clone(DSAVLTreeNode<std::string, T>*& node) {
    if(node == nullptr){
        return nullptr;
    }
    DSAVLTreeNode<std::string,T>* left = clone(node->left);
    DSAVLTreeNode<std::string,T>* right = clone(node->right);
    return new DSAVLTreeNode<std::string,T>(node->key,node->value,left,right);
}

template<class T>
DSAVLTreeNode<std::string, T> *DSAVLTree<std::string, T>::get_root() const{
    return root;
}

template<class T>
T *DSAVLTree<std::string, T>::get(const std::string& key) {
    DSAVLTreeNode<std::string,T> *node = root;
    return get(key, node);
}

template<class T>
inline T *DSAVLTree<std::string, T>::get(const std::string& key, DSAVLTreeNode<std::string, T> *&node) {
    if(node == nullptr){
        return nullptr;
    }
    int compare = strcmp(node->key.c_str(), key.c_str());
    if(compare == 0){
        return &node->value;
    }
    if(compare < 0){
        return get(key, node->right);
    }
    else{
        return get(key, node->left);
    }
}

template<class T>
std::vector<DSAVLTreeNode<std::string, T>> DSAVLTree<std::string, T>::getVectOfElements() {
    std::vector<DSAVLTreeNode<std::string, T>> vect;
    getVectOfElementsHelper(root, vect);
    return vect;
}

template<class T>
void DSAVLTree<std::string, T>::getVectOfElementsHelper(const DSAVLTreeNode<std::string, T> *node,
                                                        std::vector<DSAVLTreeNode<std::string, T>> &vect) {
    if(node == nullptr){
        return;
    }
    getVectOfElementsHelper(node->left, vect);
    vect.push_back(*node);
    getVectOfElementsHelper(node->right, vect);
}

template<class T>
void
DSAVLTree<std::string, T>::printFileHelper(std::fstream &outfs, const DSAVLTreeNode<std::string, T> *node) {
    if(node == nullptr){
        return;
    }
    printFileHelper(outfs,node->left);
    outfs << node->key << " ";
    for(auto &c : node->value){
        outfs << c->paper_id << " ";
    }
    outfs << std::endl;
    printFileHelper(outfs, node->right);
}

template<class T>
void DSAVLTree<std::string, T>::printTreeToFile(std::string filename) {
    std::fstream outfs(filename);
    if(!outfs.is_open()){
        std::cout << "file failed to open: " << filename << std::endl;
        assert(false);
    }
    printFileHelper(outfs, root);
    outfs.close();
}

