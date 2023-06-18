#include "../inc/meters.hpp"
#include <cstddef> //for size_t

size_t numberOfComparisons( bool reset /*= false*/)
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