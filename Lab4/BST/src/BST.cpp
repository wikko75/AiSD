#include <iostream>
#include <algorithm>
#include "BST.hpp"
//#include "C:\studia\II_rok\semestr_4\AiSD\Laby\Lab4\Meters\inc\meters.hpp"

void BST::insertKey(int key)
{
    /*new node to insert*/
    //----------------------------------
    Node* insertedNode = new Node();
    insertedNode->key = key;
    //----------------------------------

    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr)
    {
        y = x;
        if (key < x->key)
        {
            x = x->left;
        }
        else 
        {
            x = x->right;
        } 
    }

    insertedNode->parent = y;

    if (y == nullptr)
    {
        root = insertedNode;   //empty tree, set new node as a root
    }
    else if (key < y->key)
    {
        y->left = insertedNode;
    }
    else
    {
        y->right = insertedNode;
    }   
}

void BST::deleteNode(int key)
{
    Node* nodeToDelete = getNode(root, key);

    if (nodeToDelete == nullptr)
    {
        std::cerr << "[DELETE - ERROR] Node with key: " << key << " does not exist in BST.\n";
        return;
    }  


    /*Has potential right child*/
    if (nodeToDelete->left == nullptr)
    {
        transplant(nodeToDelete, nodeToDelete->right);
    }

    /*Has potential left child*/
    else if (nodeToDelete->right == nullptr)
    {
        transplant(nodeToDelete, nodeToDelete->left);
    }

    /*Has both children*/
    else
    {
        Node* node = treeMinimum(nodeToDelete->right);

        if (node->parent != nodeToDelete)
        {
            transplant(node, node->right);
            node->right = nodeToDelete->right;
            node->right->parent = node;
        }

        transplant(nodeToDelete, node);
        node->left = nodeToDelete->left;
        node->left->parent = node;        
    }  

    delete nodeToDelete; 
}


Node* BST::treeMaximum(Node* node)
{
    while (node->right != nullptr)
    {
        node = node->right;
    }

    return node;   
}

Node* BST::getNode(Node* node, int key)
{
    if (node == nullptr) return nullptr;

    if (key == node->key) return node;

    if (key < node->key)
    {
        return getNode(node->left, key);
    }
    else
    {
        return getNode(node->right, key);
    } 
}

Node* BST::treeMinimum(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }

    return node;  
}


Node* BST::treeSuccessor(Node* node)
{
    if (node->right != nullptr)
    {
        return treeMinimum(node->right);
    }

    Node* successor = node->parent;

    while (successor != nullptr && node == successor->right)
    {
        node = successor;
        successor = successor->parent;
    }

    return successor;  
}

Node* BST::treePredecessor(Node* node)
{
    if (node->left != nullptr)
    {
        return treeMaximum(node->left);
    }

    Node* predecessor = node->parent;

    while (predecessor != nullptr && node == predecessor->left)
    {
        node = predecessor;
        predecessor = predecessor->parent;
    }


    return predecessor;   
}

int BST::getHeight(Node* node)
{
    if (node == nullptr)
    {
        return -1;
    }

    return  1 + std::max(getHeight(node->left), getHeight(node->right));
}


void BST::transplant(Node* firstSubtreeRoot, Node* secondSubtreeRoot)
{
    if (firstSubtreeRoot->parent == nullptr)
    {
        root = secondSubtreeRoot;
    }
    else if (firstSubtreeRoot == firstSubtreeRoot->parent->left)
    {

        firstSubtreeRoot->parent->left = secondSubtreeRoot;
    }
    else 
    {
        firstSubtreeRoot->parent->right = secondSubtreeRoot;       
    }

    if (secondSubtreeRoot != nullptr)
    {
        secondSubtreeRoot->parent = firstSubtreeRoot->parent;
    }

    //delete firstSubtreeRoot;
}

