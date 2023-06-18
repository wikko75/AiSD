#include <iostream>
#include <iomanip>
#include "sortingAlgo.hpp"
#include "meters.hpp"
#include "dataGen.hpp"

int main()
{
    std::cout << "\n---Sorting Algorithms---\n\n";
    std::cout << "Choose algorithm:\n"
                 "1. Insertion Sort\n"
                 "2. Merge Sort\n"
                 "3. Quick Sort\n"
                 "4. Dual Pivot Quick Sort\n\n"
                  ": ";
    
    int algorithm{};
    std::cin >> algorithm;

    std::cout << "\n=================\n\n";

    int length {getArrayLength()};
    int* array = new int[length];

    std::cout << "=================\n\n";
    std::cout << "Data order:\n"
                 "1. Descending\n"
                 "2. Random\n"
                 "3. Ascending\n\n"
                  ": ";


    int dataOrder{};
    std::cin >> dataOrder;
    std::cout << "\n";

    switch (dataOrder)
    {
    case 1:
        descendingData(array, length);
        break;
    case 2:
        randomData(array, length);
        break;
    case 3:
        ascendingData(array, length);
        break;
    default:
        std::cout << "Wrong input xd\n";
        delete[] array;
        return 1;
    }

    std::cout << "=================\n\n";

    if(length <= 40)
    {
        std::cout << "Input Array: \n";

        for(int i{0}; i < length; ++i)
        {
            std::cout << std::setw(2) << std::setfill('0') << array[i] << " ";
        }

        std::cout << "\n\n";
    }

    switch (algorithm)
    {
    case 1:
        insertionSort(array, length);
        break;
    case 2:
        mergeSort(array, 0, length - 1);
        break;
    case 3:
        quickSort(array, 0, length -1);
        break;
    case 4:
        dualPivotQuickSort(array, 0, length -1);
        break;
    default:
        std::cout << "Wrong input xd\n";
        delete[] array;
        return 1;
    }

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
    
    if (algorithm == 2)
    {
        std::cout <<"Number of merges: " << numberOfMerges(true) << "\n";
    }
    std::cout << "\n";

    delete[] array;

    return 0;
}