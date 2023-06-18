#pragma once
#include "../inc/node.hpp"


class RB_BST
{
    public:
    /// @brief root of RB_BST
    Node* root;

    /// @brief RB_BST guard
    Node* nil;

    RB_BST()
    {
        nil = new Node();
        nil->color = 0;
        root = nil;
    }

    ~RB_BST()
    {
        delete nil;
    }

    /// @brief Inserts new node to RB_BST
    /// @param key key of inserting node
    void insertKey(int key);

    /// @brief Fix-up procedure after inserting new node into RB_BST
    /// @param insertedNode  inserted node 
    void rbInsertFixup(Node* insertedNode);

    /// @brief Deletes node from RB_BST
    /// @param key key of node to delete
    void deleteNode(int key);

    /// @brief Fix-up procedure after deleting new node into RB_BST
    void rbDeleteFixup(Node* node);

    /// @brief Performs left rotate operation on provided node
    /// @param node node to perform rotation on
    void leftRotate(Node* node);

    /// @brief Performs right rotate operation on provided node
    /// @param node node to perform rotation on
    void rightRotate(Node* node);

    /// @brief Used in deleting node from RB-BST
    void rbTransplant(Node* firstSubtreeRoot, Node* secondSubtreeRoot);

    /// @brief Gets node having given key
    /// @param key of node you want to retrive
    /// @param node node you want to start searching from (probably root of RB_BST :d)
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

    /// @brief Gets height of subtree 
    /// @param node root of subtree
    /// @return integer - height; -1 if subtree does not exists 
    int getHeight(Node* node);
};
