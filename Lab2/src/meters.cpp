#include <iostream>
#include <iomanip>
#include "meters.hpp"


int numberOfShifts(bool reset /*= false*/)
{
    static int count{};

    if(reset)
    {
        int result = count;
        count = 0;

        return result;
    }

    return ++count;
}

int numberOfComparisons( bool reset /*= false*/)
{
    static int count{};

    if(reset)
    {
        int result = count;
        count = 0;

        return result;
    }

    return ++count;
}

int numberOfMerges(bool reset /*= false*/)
{
    static int count{};

    if(reset)
    {
        int result = count;
        count = 0;

        return result;
    }

    return ++count;
}

void logAfterMerge(int array[], const int leftIdx, const int rightIdx)
{
    static int count{};
    ++count;

    std::cout << count << ". MERGE: \n";
    for(int i{leftIdx}; i <= rightIdx; ++i)
    {
        std::cout << std::setw(2) << std::setfill('0') << array[i] << " ";
    }

    std::cout << "\n\n";
}

bool isSorted(int array[], const int length)
{
    if (length == 1)
    {
        return true;
    }

    for (int i{0}; i < length-1; ++i)
    {
        if(array[i] > array[i+1])
        {
            return false;
        }
    }

    if(array[length-2] > array[length-1])
    {
        return false;
    }

    return true;
}
