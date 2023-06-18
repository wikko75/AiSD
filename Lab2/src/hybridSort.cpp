#include<iostream>
#include <iomanip>
#include "dataGen.hpp"
#include "meters.hpp"
#include "sortingAlgo.hpp"


void hybridSort(int array[], int leftIdx, int rightIdx, int threshold)
{
    if (leftIdx >= rightIdx)
    {
        return;
    }

    if(rightIdx - leftIdx <= threshold)
    {
        insertionSort(array, rightIdx-leftIdx);
    }
    
    int midIdx = (rightIdx + leftIdx)/2;
    hybridSort(array, leftIdx, midIdx);
    hybridSort(array, (midIdx + 1), rightIdx);

    merge(array, leftIdx, midIdx, rightIdx);
}



int main()
{
    return 0;
}