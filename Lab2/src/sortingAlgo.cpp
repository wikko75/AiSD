#include<iostream>
#include <iomanip>
#include "sortingAlgo.hpp"
#include "dataGen.hpp"
#include "meters.hpp"


//==========================================================================
//-------------------------INSERTION-SORT-----------------------------------
//==========================================================================

void insertionSort(int array[], int size)
{    
    for(int i{1}; i < size; ++i)
    {
        int key{ array[i] };
        int j { i-1 };

        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            numberOfShifts();
            //array[i] = array[j]; //doesnt work - why?
            --j;
            numberOfComparisons();
        }
        numberOfComparisons();
        array[j+1] = key;

    }
}


//==========================================================================
//-------------------------MERGE-SORT---------------------------------------
//==========================================================================

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
    int k {0};   // rigth side indices
    for (int i{leftIdx}; i < rigthIdx + 1; ++i)
    {
        //================================================
        //Checks whether left/rigth idx goes out of range
        if(j > (midIdx - leftIdx))
        {
            array[i] = B[k];
            ++k;
            continue;
        }

        if(k > (rigthIdx - (midIdx + 1)))
        {
            array[i] = A[j];
            ++j;
            continue;
        }
        //================================================

        if(A[j] <= B[k])  
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
    //logAfterMerge(array, leftIdx, rigthIdx);
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




//==========================================================================
//-------------------------QUICK-SORT---------------------------------------
//==========================================================================

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
        if (array[j] <= x)
        {
            swap(array, i, j);
            numberOfShifts();   //czy jezeli przestawiam z samym soba to liczyc do liczby przestawien?
            numberOfComparisons();
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




//==========================================================================
//-------------------------DOUBLE-PIVOT-QUICK-SORT--------------------------
//==========================================================================

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



    if(leftIdx + s == qPosition)            //mayby p > q is better?
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