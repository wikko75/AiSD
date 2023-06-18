#include "meters.hpp"

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


int readAndAssignCount(bool reset /*= false*/)
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