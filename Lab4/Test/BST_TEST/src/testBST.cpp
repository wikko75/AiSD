#include <iostream>
#include <algorithm>
#include<random>
#include "BST.hpp"
#include "dataGen.hpp"
#include "testBST.hpp"


void testBST1(int noOfKeys)
{
    std::cout << "---------------------------------------------------\n\nTesting - inserting ascending keys to BST and deleting random keys from BST\n\n";

    BST* tree = new BST();   

    int keys[noOfKeys];

    ascendingData(keys, noOfKeys);

    std::cout << "Inserting " << noOfKeys << " ascending keys...\n";

    for (int key : keys)
    {
        tree->insertKey(key);
    }

    std::cout << "\n\nInserted keys: \n";
    for (int key : keys)
    {
        std::cout << key << "\n";
    }
    
    std::cout << "\n\n";

    for (int key : keys)
    {
        std::cout <<"Key: " << tree->getNode(tree->root, key)->key << "\n";
        std::cout <<"Node height: " << tree->getHeight(tree->getNode(tree->root, key)) << "\n\n";
    }

    std::cout << "\n\n";

    std::mt19937 mt{ std::random_device{}() }; 
    std::cout << "Shuffling array of keys...\n";
    std::shuffle(keys, keys + noOfKeys, mt);

    for (int key : keys)
    {
        std::cout << key << "\n";
    }

    std::cout << "\n\nDeleting keys...\n";
    for (int key : keys)
    {
        tree->deleteNode(key);
        std::cout <<  "Deleted: "<< key << "\nTree height: " << tree->getHeight(tree->root) <<  "\n\n";
    }

    delete tree;
    std::cout << "---------------------------------------------------\nTEST PASSED\n";

}


void testBST2(int noOfKeys)
{
    std::cout << "---------------------------------------------------\n\nTesting - inserting random keys to BST and deleting random keys from BST\n\n";
    BST* tree = new BST();   

    int keys[noOfKeys];

    randomData(keys, noOfKeys);

    std::cout << "Inserting " << noOfKeys << " random keys...\n";

    for (int key : keys)
    {
        tree->insertKey(key);
    }

    std::cout << "\n\nInserted keys: \n";
    for (int key : keys)
    {
        std::cout << key << "\n";
    }
    
    std::cout << "\n\n";

    for (int key : keys)
    {
        std::cout <<"Key: " << tree->getNode(tree->root, key)->key << "\n";
        std::cout <<"Node height: " << tree->getHeight(tree->getNode(tree->root, key)) << "\n\n";
    }

    std::cout << "\n\n";
    
    std::mt19937 mt{ std::random_device{}() }; 
    std::cout << "Shuffling array of keys...\n";
    std::shuffle(keys, keys + noOfKeys, mt);

    for (int key : keys)
    {
        std::cout << key << "\n";
    }

    std::cout << "\n\nDeleting keys...\n";
    for (int key : keys)
    {
        tree->deleteNode(key);
        std::cout <<  "Deleted: "<< key << "\nTree height: " << tree->getHeight(tree->root) <<  "\n\n";
    }

    delete tree;
    std::cout << "---------------------------------------------------\nTEST PASSED\n";
}