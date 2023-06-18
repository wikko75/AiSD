#include<iostream>
#include <iomanip>
#include "dataGen.hpp"
#include "meters.hpp"

void merge(int array[], int leftIdx, int midIdx, int rigthIdx)
{
    int ALength = midIdx - leftIdx + 1;
    int BLength = rigthIdx - midIdx;

    int A[ALength]; 
    int B[BLength];

    for(int i{0}; i < ALength; ++i)
    {
        A[i] = array[leftIdx + i]; //right side
    }

    for(int i{0}; i < BLength; ++i)
    {
        B[i] = array[(midIdx + 1) + i]; //left side
    }

    int j {0};   // left side indices
    int k {0};  // rigth side indices
    for (int i{leftIdx}; i < rigthIdx + 1; ++i)
    {
        //================================================
        //Checks whether left/rigth idx goes out of range
        if(j > (midIdx - leftIdx))
        {
            array[i] = B[k];
            numberOfShifts();
            ++k;
            continue;
        }

        if(k > (rigthIdx - (midIdx + 1)))
        {
            array[i] = A[j];
            numberOfShifts();
            ++j;
            continue;
        }
        //================================================

        if( A[j] <= B[k])  
        {
            array[i] = A[j];
            numberOfComparisons();
            ++j;
        }
        else
        {
            array[i] = B[k];
            numberOfComparisons();
            numberOfShifts();
            ++k;
        }
    }
    
    numberOfMerges();
    logAfterMerge(array, leftIdx, rigthIdx);
}

void mergeSort(int array[], int leftIdx, int rightIdx)
{
    if (leftIdx >= rightIdx)
    {
        return;
    }
    
    int midIdx = (rightIdx + leftIdx)/2;
    mergeSort(array, leftIdx, midIdx);
    mergeSort(array, (midIdx + 1), rightIdx);

    merge(array, leftIdx, midIdx, rightIdx);
}


int main()
{
    //=====================================================================
    //--------------------------tests--------------------------------------
    //=====================================================================

    std::cout << "-----------------------------------------------\n";

    int length{getArrayLength()};

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


    mergeSort(array, 0, length-1);

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
    std::cout <<"Number of merges: " << numberOfMerges(true) << "\n";

    delete[] array;

    return 0;
}