#pragma once
#include "../inc/node.hpp"

class BST 
{
    public:
    /// @brief root of BST
    Node* root;

    /// @brief Inserts new node to BST
    /// @param key key of inserting node
    void insertKey(int key);

    /// @brief Deletes node from BST
    /// @param key key of node to delete
    void deleteNode(int key);


    /// @brief Gets node having given key
    /// @param key of node you want to retrive
    /// @param node node you want to start searching from (probably root of BST :d)
    /// @return pointer to Node object, nullptr if node with given key does not exist
    Node* getNode(Node* node, int key);


    /// @brief Gets node with the lowes key value in subtree
    /// @param node root of subtree
    /// @return Pointer to Node object 
    Node* treeMinimum(Node* node);


    /// @brief Gets node with the highest key value in subtree
    /// @param node root of subtree
    /// @return Pointer to Node object
    Node* treeMaximum(Node* node);


    /// @brief Finds successor of node
    /// @param node node whose successor you want to retrive
    /// @return Pointer to Node object
    Node* treeSuccessor(Node* node);


    /// @brief Finds predecessor of node
    /// @param node node whose predecessor you want to retrive 
    /// @return Pointer to Node object
    Node* treePredecessor(Node* node);


    /// @brief Gets height of subtree 
    /// @param node root of subtree
    /// @return integer - height -1 if subtree does not exists 
    int getHeight(Node* node);


    /// @brief Used in deleting node from BST
    void transplant(Node* firstSubtreeRoot, Node* secondSubtreeRoot);


};