#include<iostream>
#include<random>
#include <iomanip>
#include "dataGen.hpp"

const int getArrayLength()
{
    std::cout << "Array length: ";
    int length{};
    std::cin >> length;
    std::cout << "\n";

    return length;
}

void randomData(int array[], const int length)
{
    std::mt19937 mt{ std::random_device{}() };              // Instantiate a 32-bit Mersenne Twister

    std::uniform_int_distribution number {0, 2*length - 1};
	
	for (int count{0}; count < length; ++count)
	{
		array[count] = number(mt);                         // generate a random number and insert into the array
    }
}

void ascendingData(int array[], const int length)
{
    for (int count{0}; count < length; ++count)
	{
		array[count] = count;
    }
}

void descendingData(int array[], const int length)
{
    for (int count{0}; count < length; ++count)
	{
		array[count] = length-1 - count;
    }
}