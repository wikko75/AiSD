#include<iostream>
#include <iomanip>
#include "dataGen.hpp"
#include "meters.hpp"


void insertionSort(int array[], int size)
{
    int comparisons{0};
    int shifts{0};
    
    for(int i{1}; i < size; ++i)
    {
        int key{ array[i] };
        int j { i-1 };

        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            numberOfShifts();
            //array[i] = array[j]; //tak nie dziala - mega ciekawe
            --j;
            numberOfComparisons();
        }
        numberOfComparisons();
        array[j+1] = key;

    }
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


    insertionSort(array, length);

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


    std::cout << "\n\nNumber of Comparisons : " << numberOfComparisons(true) << "\n";
    std::cout <<"Number of shifts: " << numberOfShifts(true) << "\n";

    
    delete[] array;

    return 0;
}