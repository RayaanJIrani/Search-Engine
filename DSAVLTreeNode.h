//
// Created by Saaketh Koka on 4/6/21.
//

#pragma once
#include <iostream>

template<class A, class T>
class DSAVLTreeNode{
    template<class U, class Y> friend class DSAVLTree;
private:
    A key;
    T value;
    DSAVLTreeNode<A,T>* left;
    DSAVLTreeNode<A,T>* right;
    int height;

public:

    /**
     * Default Constructor - generates the node from component parts
     * @param key - key field of the node
     * @param value - value field of the node
     * @param after - node which is to the left of the node (nullptr if empty)
     * @param before - node which is to the right of the node (nullptr if empty)
     */
    DSAVLTreeNode(A key, T value, DSAVLTreeNode* after = nullptr, DSAVLTreeNode* before = nullptr);

    /**
     * Default Constructor - creates a DSAVLTreeNode with all empty fields.
     */
    DSAVLTreeNode();

    /**
     * Returns key of node
     * @return A key - key of *this (by reference)
     */
    A& get_key();

    /**
     * Returns value of node
     * @return T value - Returns value of *this (by reference)
     */
    T& get_value();

    /**
     * Returns the node to the left of the node
     * @return DSAVLTreeNode<A,T> node - returns the node (by reference) to the left of *this pointer
     */
    DSAVLTreeNode<A,T>*& get_left();

    /**
     * Returns the node to the right of the node
     * @return DSAVLTreeNode<A,T> node - returns the node (by reference) to the right of *this pointer
     */
    DSAVLTreeNode<A,T>*& get_right();

};

template<class A, class T>
DSAVLTreeNode<A, T>::DSAVLTreeNode(A key, T value, DSAVLTreeNode *left, DSAVLTreeNode *right) {
    this->key = key;
    this->value = value;
    this->left = left;
    this->right = right;
    this->height = 0;
}
//acessors
template<class A, class T>
A& DSAVLTreeNode<A, T>::get_key(){
    return key;
}

template<class A, class T>
T& DSAVLTreeNode<A, T>::get_value(){
    return value;
}

template<class A, class T>
DSAVLTreeNode<A, T>*& DSAVLTreeNode<A, T>::get_left(){
    return left;
}

template<class A, class T>
DSAVLTreeNode<A, T>*& DSAVLTreeNode<A, T>::get_right(){
    return right;
}

template<class A, class T>
DSAVLTreeNode<A, T>::DSAVLTreeNode() {

}













