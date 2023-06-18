#pragma once

class Node
{
    public:
    int key;
    Node* parent;
    Node* left;
    Node* right;
    bool color;   //black ==  0;  red == 1
};