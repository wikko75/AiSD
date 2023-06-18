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

void partition(int array[], int leftIdx, int rightIdx, int& pPivot, int& qPivot)
{
    int p {array[leftIdx]};
    int q {array[rightIdx]};
 

    int s {};
    int l {};

    if(p > q)
    {
        int temp = p;
        p = q;
        q = temp;

        swap(array, leftIdx, rightIdx);
        numberOfShifts();
    }

    int i {leftIdx};
    int k {rightIdx};

    int pPosition{i};
    int qPosition{k};

    if ((rightIdx - leftIdx) == 1)   //just two elements in the array, so its sorted
    {
        pPivot = pPosition;
        qPivot = qPosition;

        return;
    }

    for (int j{leftIdx + 1}; j < rightIdx; ++j)
    {
        if(k < j)
        {
            break;
        }

        if (s >= l)
        {
            numberOfComparisons();
            if (array[j] < p)
            {   
                if(i == pPosition)
                {
                    pPosition = j;
                }
                if (i == qPosition)
                {
                    qPosition = j;
                }

                swap(array, i, j);
                numberOfShifts();   //czy jezeli przestawiam z samym soba to liczyc do liczby przestawien?
                ++s;
                ++i;
                continue;
            }
            else if (array[j] > q)
            {
                if(k == qPosition)
                {
                    qPosition = j;
                }

                if (l == 0)
                {
                    swap(array, k, j);
                    numberOfShifts();   
                    ++l;
                    --k;
                }
                else
                {
                    swap(array, k, j);
                    numberOfShifts();   
                    ++l;
                    --k;
                    --j;
                }
            }  
            numberOfComparisons();
        }
        else
        {
            numberOfComparisons();
            if (array[j] > q)
            {
                if(k == qPosition)
                {
                    qPosition = j;
                }
                if (l == 0)
                {
                    swap(array, k, j);
                    numberOfShifts();   
                    ++l;
                    --k;
                }
                else
                {
                    swap(array, k, j);
                    numberOfShifts();   
                    ++l;
                    --k;
                    --j;
                }
            }
            else if(array[j] < p)
            {
                if(i == pPosition)
                {
                    pPosition = j;
                }
                if (i == qPosition)
                {
                    qPosition = j;
                }
                swap(array, i, j);
                numberOfShifts();   
                ++s;
                ++i;
            }
            numberOfComparisons();
        }
    }



    if(leftIdx + s == qPosition)            //maybe p>q better?
    {
        swap(array, pPosition, leftIdx + s);
        numberOfShifts();
        qPosition = pPosition;
        pPosition = leftIdx + s;

        swap(array, qPosition, rightIdx - l);
        numberOfShifts();
        qPosition = rightIdx - l;
    }
    else
    {
        swap(array, pPosition, leftIdx + s);
        numberOfShifts();
        pPosition = leftIdx + s;

        swap(array, qPosition, rightIdx - l);
        numberOfShifts();
        qPosition = rightIdx - l;
    }


    pPivot = pPosition;
    qPivot = qPosition;
    

}


void dualPivotQuickSort(int array[], int leftIdx, int rightIdx)
{
    if(leftIdx < rightIdx)
    {
        int pPivot{};
        int qPivot{};
        partition(array, leftIdx, rightIdx, pPivot, qPivot);

        dualPivotQuickSort(array, leftIdx, pPivot -1);
        dualPivotQuickSort(array, pPivot, qPivot - 1);
        dualPivotQuickSort(array, qPivot, rightIdx);

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


    dualPivotQuickSort(array, 0, length-1);

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