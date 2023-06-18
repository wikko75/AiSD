#include<iostream>
#include <iomanip>
#include "dataGen.hpp"
#include "meters.hpp"

void swap(int array[], int x, int y)
{
    int temp = array[x];

    array[x] = array[y];

    array[y] = temp;
}

int lomutoPartition(int array[], int leftIdx, int rightIdx)
{
    int x {array[rightIdx]};
    int i {leftIdx};

    for (int j{leftIdx}; j < rightIdx; ++j)
    {
        numberOfComparisons();
        if (array[j] <= x)
        {
            swap(array, i, j);
            numberOfShifts();   //czy jezeli przestawiam z samym soba to liczyc do liczby przestawien?
            ++i;
        }
    }

    swap(array, i, rightIdx);
    numberOfShifts();

    return i;
}

void quickSort(int array[], int leftIdx, int rightIdx)
{
    if(leftIdx < rightIdx)
    {
        int pivot = lomutoPartition(array, leftIdx, rightIdx);
        quickSort(array, leftIdx, pivot - 1);
        quickSort(array, pivot + 1 , rightIdx);
    }
}

int main()
{
    
    //=====================================================================
    //--------------------------tests--------------------------------------
    //=====================================================================

    int length {getArrayLength()};
    int* array = new int[length];
    
    randomData(array, length);
    
    if(length <= 40)
    {
        std::cout << "Input Array: \n";

        for(int i{0}; i < length; ++i)
        {
            std::cout << std::setw(2) << std::setfill('0') << array[i] << " ";
        }

        std::cout << "\n\n";
    }


    quickSort(array, 0, length - 1);

    if(isSorted(array, length))
    {
        std::cout << "Array sorted correctly\n";
    }
    else
    {
        std::cout << "Array not sorted correctly!\n";

        delete[] array;
        return 1;
    }


    if(length <= 40)
    {
        std::cout << "\nOutput Array: \n";

        for(int i{0}; i < length; ++i)
        {
            std::cout << std::setw(2) << std::setfill('0') << array[i]<< " ";
        }

        std::cout << "\n\n";
    }

    std::cout << "\nNumber of Comparisons : " << numberOfComparisons(true) << "\n";
    std::cout <<"Number of shifts: " << numberOfShifts(true) << "\n";

    delete[] array;
    return 0;
}