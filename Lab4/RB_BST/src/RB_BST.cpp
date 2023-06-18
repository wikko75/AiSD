#include <iostream>
#include "../inc/node.hpp"
#include "RB_BST.hpp"

void RB_BST::insertKey(int key)
{
    /*new node to insert*/
    //----------------------------------
    Node* insertedNode = new Node();
    insertedNode->key = key;
    //----------------------------------

    Node* y = nil;  
    Node* x = root;

    while (x != nil)
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

    if (y == nil)  
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

    insertedNode->left = nil;
    insertedNode->right = nil;
    insertedNode->color = 1;
    rbInsertFixup(insertedNode);
}

void RB_BST::rbInsertFixup(Node *insertedNode)
{
    while (insertedNode->parent->color == 1) 
    {
        if (insertedNode->parent == insertedNode->parent->parent->left)
        {
            Node* y = insertedNode->parent->parent->right;

            if (y->color == 1)
            {
                insertedNode->parent->color = 0;
                y->color = 0;
                insertedNode->parent->parent->color = 1;
                insertedNode = insertedNode->parent->parent;
            }
            else
            {
                if (insertedNode == insertedNode->parent->right)
                {
                    insertedNode = insertedNode->parent;
                    leftRotate(insertedNode);
                }

                insertedNode->parent->color = 0;
                insertedNode->parent->parent->color = 1;
                rightRotate(insertedNode->parent->parent);
            } 
        }
        else
        {
            Node* y = insertedNode->parent->parent->left;

            if (y->color == 1)
            {
                insertedNode->parent->color = 0;
                y->color = 0;
                insertedNode->parent->parent->color = 1;
                insertedNode = insertedNode->parent->parent;
            }
            else
            {
                if (insertedNode == insertedNode->parent->left)
                {
                    insertedNode = insertedNode->parent;
                    rightRotate(insertedNode);
                }

                insertedNode->parent->color = 0;
                insertedNode->parent->parent->color = 1;
                leftRotate(insertedNode->parent->parent);
            }   
        }

        if (insertedNode == root)
        {
            break;
        }
         
    }

    root->color = 0;
}

void RB_BST::deleteNode(int key)
{
    Node* z = getNode(root, key);

    if (z == nil)
    {
        std::cerr << "[DELETE - ERROR] Node with key: " << key << " does not exist in RB-BST.\n";
        return;
    }

    Node* y = z;
    bool yColor = y->color;
    Node* x;

    if (z->left == nil)
    {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == nil)
    {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else
    {
        y = treeMinimum(z->right);
        yColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yColor == 0)
    {
        rbDeleteFixup(x); 
    }

    delete z; 
}

void RB_BST::rbDeleteFixup(Node *node)
{
    while (node != root && node->color == 0)
    {
        if (node == node->parent->left)
        {
            Node* w = node->parent->right;

            if (w->color == 1)
            {
                w->color = 0;
                node->parent->color = 1;
                leftRotate(node->parent);
                w = node->parent->right;
            }

            if (w->left->color == 0 && w->right->color == 0)
            {
                w->color = 1;
                node = node->parent;
            }
            else
            {
                if (w->right->color == 0)
                {
                    w->left->color = 0;
                    w->color = 1;
                    rightRotate(w);
                    w = node->parent->right;
                }
                    
                w->color = node->parent->color;
                node->parent->color = 0;
                w->right->color = 0;
                leftRotate(node->parent);
                node = root;  
            }
        }
        else
        {
            Node* w = node->parent->left;

            if (w->color == 1)
            {
                w->color = 0;
                node->parent->color = 1;
                rightRotate(node->parent);
                w = node->parent->left;
            }

            if (w->right->color == 0 && w->left->color == 0)
            {
                w->color = 1;
                node = node->parent;
            }
            else
            {
                if (w->left->color == 0)
                {
                    w->right->color = 0;
                    w->color = 1;
                    leftRotate(w);
                    w = node->parent->left;
                }
                
                w->color = node->parent->color;
                node->parent->color = 0;
                w->left->color = 0;
                rightRotate(node->parent);
                node = root;
            }
        }     
    }

    node->color = 0;    
}

void RB_BST::leftRotate(Node *node)
{
    Node* y = node->right;
    node->right = y->left;
    
    if (y->left != nil)
    {
        y->left->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nil)   
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
}

void RB_BST::rightRotate(Node *node)
{
    Node* y = node->left;
    node->left = y->right;
    
    if (y->right != nil)
    {
        y->right->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nil)     
    {
        root = y;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = y;
    }
    else
    {
        node->parent->left = y;
    }

    y->right = node;
    node->parent = y;
}

void RB_BST::rbTransplant(Node *firstSubtreeRoot, Node *secondSubtreeRoot)
{
    if (firstSubtreeRoot->parent == nil)
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

    secondSubtreeRoot->parent = firstSubtreeRoot->parent;
}

Node* RB_BST::getNode(Node* node, int key)
{
    if (node == nil) return nullptr;

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

Node *RB_BST::treeMinimum(Node *node)
{
    while (node->left != nil)
    {
        node = node->left;
    }

    return node;
}

Node *RB_BST::treeMaximum(Node *node)
{
    while (node->right != nil)
    {
        node = node->right;
    }

    return node;
}

int RB_BST::getHeight(Node *node)
{
    if (node == nil)
    {
        return -1;
    }

    return  1 + std::max(getHeight(node->left), getHeight(node->right));
}
