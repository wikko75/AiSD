#pragma once 

class Node
{
    public:
    /// @brief Value stored by node
    int key;
    /// @brief Pointer to node's parent
    Node* parent;
    /// @brief Pointer to node's left child
    Node* left;
    /// @brief Pointer to node's right child
    Node* right;

};