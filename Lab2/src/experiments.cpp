#include <iostream>
#include <fstream>
#include "sortingAlgo.hpp"
#include "meters.hpp"
#include "dataGen.hpp"

int main ()
{

    std::ofstream file;
    
    file.open("insertionSort.csv", std::ios::out | std::ios::app);

    int length{getArrayLength()};

    int* array = new int[length];

    for(int k{0}; k < 2; ++k)
    {
        randomData(array, length);
        insertionSort(array, length);

        int comparisons {numberOfComparisons(true)};
        int shifts {numberOfShifts(true)};

        std::cout << comparisons << "\n";
        file << comparisons << "\n";

        std::cout << shifts << "\n\n";
        file << shifts << "\n";
    }

    file.close();

    return 0;
}