//
// Created by Saaketh Koka on 4/6/21.
//
#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "DSAVLTreeNode.h"
#include <vector>

template<class A, class T>
class DSAVLTree{
private:
    DSAVLTreeNode<A,T> *root;

    // Or we can caluclate the number of nodes when we want to output the stats (easier):
    /**
     * Recursivly inserts a key value pair into the AVLTree with root node t, and rebalances the Tree.
     * @param key - key of the item being inserted
     * @param value - value of item being inserted
     * @param t - the node which the is the root of the tree the key value pair is being inserted into
     */
    inline void insert(const A &key, const T &value, DSAVLTreeNode<A,T> *&t);
    /**
     * Takes actions which ensures that the binary tree with root node t retains the property of an AVLTree
     * @param t - the root node of the AVL Tree being balanced
     */
    inline void balance(DSAVLTreeNode<A,T> *&t);


    /**
     * A helper method to contains which returns if key A is in tree with root node
     * @param key - the key which is checked to see if within tree
     * @param node - the node which is the root node of the tree
     * @return - a bool value if key is in the tree
     */
    inline bool contains(const A& key, DSAVLTreeNode<A,T>*& node) const;

    /**
     * A method which returns the value of a key in the tree with root node node.
     * @param key - The key of the value pair which a response is looked for
     * @param node - the root node of the tree
     * @return T - the value of the key being looked for. If key input is not found in tree method throws std::invalid_argument
     */
    inline T*& get(const A& key, DSAVLTreeNode<A,T>*& node);

    //print methods
    /**
     * Prints the tree with root node node in pre-order
     * @param node - the root node of the tree being printed
     */

    void printPreOrder(const DSAVLTreeNode<A,T>* node) const;

    /**
     * Prints the tree with root node node in in-Order
     * @param node - the root node of the tree being printed
     */

    void printInOrder(const DSAVLTreeNode<A,T>* node) const;

    /**
     * Prints the tree with root node node in post-order
     * @param node - the root node of the tree being printed
     */
    void printPostOrder(const DSAVLTreeNode<A,T>* node) const;

    // Rotation Methods:
    /**
     *  Resolves the type I imbalance by rotating the left branch
     *  @param node - the node which is the root of the tree in which the first imbalance exists
     */
    inline void rotateWithLeftChild(DSAVLTreeNode<A,T>*& node);

    /**
     *Resolves the type II imbalance by generating a type I error and then resolving it using a left rotation
     * @param node - the node which is the root of the tree in which the first imbalance exists
     */
    inline void rotateWithRightChild(DSAVLTreeNode<A,T>*& node);

    /**
     * Resolves the type III imbalance by rotating the right branch
     * @param node - the node which is the root of the tree in which the first imbalance exists
     */
    inline void doubleWithLeftChild(DSAVLTreeNode<A,T>*& node);

    /**
     * Resolves the type IV imbalance by generating a type III erorr and then resolving it using a right rotation.
     * @param node - the node which is the root of the tree in which the first imbalance exists
     *
     */
    inline void doubleWithRightChild(DSAVLTreeNode<A,T>*& node);

    // Get Height of node:
    /**
     * determines the height of the tree with root node.
     * @param node
     * @return height
     */
    int getHeight(DSAVLTreeNode<A,T> *&node);

    /**
     * generates a deep copy of the tree with root node.
     * @param node
     * @return root node of cloned tree
     */
    DSAVLTreeNode<A,T>* clone(DSAVLTreeNode<A,T>*& node);

    /**
     * Deallocates all nodes in the tree with root node.
     * @param node
     */
    void destructorHelper(DSAVLTreeNode<A,T>*& node);



public:
    /**
     * root node constructor (and default) - Generates deep copy of tree with root root.
     * @param root - root node of tree which is being copied (by default nullptr representing empty tree)
     */
    DSAVLTree(DSAVLTreeNode<A,T>* root = nullptr);

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
    void insert(const A& key, const T& value);

    /**
     * Inserts an AVLTree Node into the Tree and then balance's it.
     * @param DSAVLTreeNode
     */
    void insert(const DSAVLTreeNode<A,T>*& node);

    /**
     * Output's whether or not a certain key is found in the tree.
     * @param key
     * @return bool
     */
    bool contains(const A& key) const;

    /**
     * returns the value of the node with key of key in tree
     * @param key
     * @return T - the value of node with key of key
     */
    T*& get(const A& key);

    /**
     * Assignment Operator
     * @param tree to be copied
     * @return DSAVLTree
     */
    DSAVLTree<A,T>& operator=(const DSAVLTree<A,T>& other); //overloaded assignment operator

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
    DSAVLTreeNode<A,T>* get_root() const;

};




template<class A, class T>
DSAVLTree<A, T>::DSAVLTree(DSAVLTreeNode<A, T> *targetNode) {
    if(targetNode == nullptr){
        root = nullptr;
        return;
    }
    this->root = clone(targetNode);
}


template<class A, class T>
DSAVLTree<A, T>::DSAVLTree(DSAVLTree &otherTree) {
    if(otherTree.root == nullptr){
        root = nullptr;
        return;
    }
    this->root = clone(otherTree.root);
}


template<class A, class T>
DSAVLTree<A, T>::~DSAVLTree() {
    destructorHelper(root);
}

template<class A, class T>
DSAVLTree<A, T>& DSAVLTree<A, T>::operator=(const DSAVLTree<A, T>& other) {
    if(this == &other){ //Checks to see if self = self
        return *this;
    }
    if(this->root != nullptr){
        this->~DSAVLTree<A,T>(); //deletes data
    }
    if(other.root == nullptr){
        this->root = nullptr; //makes root nullptr is other tree has no data
    }
    else {
        this->root = clone(other.root);
    }

    return *this;
}

template<class A, class T>
inline void DSAVLTree<A, T>::insert(const A& key, const T& value, DSAVLTreeNode<A, T> *&t) {
    if(t == nullptr){
        t = new DSAVLTreeNode<A,T>(key,value); // Once it finds an empty node it creates a new node there.
    }
    else if(t->key < key){
        insert(key, value, t->right); // Recursively searches for proper place to insert value.
    }
    else if(key < t->key){
        insert(key, value, t->left);
    }
    balance(t);
}


template<class A, class T>
inline void DSAVLTree<A, T>::balance(DSAVLTreeNode<A, T> *&t) {
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

template<class A, class T>
void DSAVLTree<A, T>::printPreOrder() const{
    printPreOrder(root);
}

template<class A, class T>
void DSAVLTree<A, T>::printPreOrder(const DSAVLTreeNode<A, T>* node) const{
    if(node == nullptr){
        return;
    }
    std::cout << node->key << ": " << node->value << std::endl;
    printPreOrder(node->left);
    printPreOrder(node->right);
}

template<class A, class T>
void DSAVLTree<A,T>::printInOrder() const{
    printInOrder(root);
}

template<class A, class T>
void DSAVLTree<A, T>::printInOrder(const DSAVLTreeNode<A, T>* node) const{
    if(node == nullptr){
        return;
    }
    printInOrder(node->left);
    std::cout << node->key << ": " << node->value << std::endl;
    printInOrder(node->right);
}

template<class A, class T>
void DSAVLTree<A, T>::printPostOrder() const {
    printPostOrder(root);
}

template<class A, class T>
void DSAVLTree<A, T>::printPostOrder(const DSAVLTreeNode<A, T>* node) const {
    if(node == nullptr){
        return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    std::cout << node->key << ": " << node->value << std::endl;
}


template<class A, class T>
void DSAVLTree<A, T>::insert(const A& key, const T& value) {
    insert(key, value, root);
}

template<class A, class T>
void DSAVLTree<A, T>::insert(const DSAVLTreeNode<A, T> *&node) {
    insert(node->key, node->value, root);
}

template<class A, class T>
int DSAVLTree<A, T>::getHeight(DSAVLTreeNode<A, T> *&node) {
    if(node == nullptr){
        return -1;
    }
    else{
        return node->height;
    }
}

template<class A, class T>
inline void DSAVLTree<A, T>::rotateWithLeftChild(DSAVLTreeNode<A, T>*& node) {
    DSAVLTreeNode<A,T> *leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    leftNode->height = std::max(getHeight(leftNode->left), node->height) + 1;
    node = leftNode;
}

template<class A, class T>
inline void DSAVLTree<A, T>::rotateWithRightChild(DSAVLTreeNode<A, T> *&node) {
    DSAVLTreeNode<A,T> *rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    rightNode->height = std::max(getHeight(rightNode->right), node->height) + 1;
    node = rightNode;
}

template<class A, class T>
inline void DSAVLTree<A, T>::doubleWithLeftChild(DSAVLTreeNode<A, T> *&node) {
    rotateWithRightChild(node->left);
    rotateWithLeftChild(node);
}

template<class A, class T>
inline void DSAVLTree<A, T>::doubleWithRightChild(DSAVLTreeNode<A, T> *&node) {
    rotateWithLeftChild(node->right);
    rotateWithRightChild(node);
}


template<class A, class T>
inline bool DSAVLTree<A, T>::contains(const A &key, DSAVLTreeNode<A, T> *&node) const {
    if(node == nullptr){
        return false;
    }
    if(node->key == key){
        return true;
    }
    if(node->key < key){
        return contains(key, node->right);
    }
    else{
        return contains(key, node->left);
    }
}

template<class A, class T>
bool DSAVLTree<A, T>::contains(const A &key) const{
    if(this->root == nullptr){
        return false;
    }
    if(this->root->key == key){
        return true;
    }
    DSAVLTreeNode<A,T> *node = root;
    return contains(key, node);
}

template<class A, class T>
void DSAVLTree<A, T>::destructorHelper(DSAVLTreeNode<A, T> *&node) {
    if(node == nullptr){
        return;
    }
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}

template<class A, class T>
DSAVLTreeNode<A, T> *DSAVLTree<A, T>::clone(DSAVLTreeNode<A, T>*& node){
    if(node == nullptr){
        return nullptr;
    }
    DSAVLTreeNode<A,T>* left = clone(node->left);
    DSAVLTreeNode<A,T>* right = clone(node->right);
    return new DSAVLTreeNode<A,T>(node->key,node->value,left,right);
}

template<class A, class T>
DSAVLTreeNode<A, T> *DSAVLTree<A, T>::get_root() const{
    return root;
}

template<class A, class T>
T *&DSAVLTree<A, T>::get(const A &key) {
    if(this->root->key == key){
        return this->root->value;
    }
    DSAVLTreeNode<A,T> *node = root;
    return get(key, node);
}

template<class A, class T>
inline T *&DSAVLTree<A, T>::get(const A &key, DSAVLTreeNode<A, T> *&node) {
    if(node == nullptr){
        throw std::invalid_argument("key not in Tree - DSAVLTree get");
    }
    if(node->key == key){
        return node->value;
    }
    if(node->key < key){
        return get(key, node->right);
    }
    else{
        return get(key, node->left);
    }
}


