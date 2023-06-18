#include <iostream>
#include <exception>
#include <random> // for std::mt19937


class popException : public std::exception
{
    virtual const char* what() const throw()
  {
    return "[No data in stack, nothing to delete]\n";
  }

} popEx;

class getException : public std::exception
{
    virtual const char* what() const throw()
  {
    return "[Can not retrive data at given index (wrong index or empty stack)]\n";
  }
} getEx;


template<class T>
class Stack
{
    private:
    T* array{};
    T* swapArray{};
    int size{};

    public:
    void push(T data)
    {
        if(size == 0)
        {
            array = new T[1];
            array[0] =  data;
            std::cout << "[push]\t Stack[" << size << "] = " << data << "\n";

            ++size;
            return;
        }

        swapArray = new T[size+1]; 

        for(int i{0}; i < size; ++i)
        {
            swapArray[i] = array[i];
        }

        delete[] array;
        array = new T[size + 1];

        for (int i{0}; i < size; ++i)
        {
            array[i] = swapArray[i];
        }

        array[size] = data;
        delete[] swapArray;

        //array = swapArray;  i o to tyle szumu bylo xdd zostawiam na pamiatke heh
        
        std::cout << "[push]\t Stack[" << size << "] = " << data << "\n";

        ++size;
    }

    T pop()
    {
        if(size == 0)
        {
            throw popEx;
        }

        T lastItem = array[size-1];
        swapArray = new T[size-1];
        
        for(int i{0}; i < size-1; ++i)
        {
            swapArray[i] = array[i];
        }

        delete[] array;
        array = new T[size - 1];

        for(int i{0}; i < size-1; ++i)
        {
            array[i] = swapArray[i];
        }

        delete[] swapArray;
        --size;
        //std::cout << "[pop]\t Stack[" << size << "]\n";

        return lastItem;
    }

    T get(int idx)
    {
        if(idx < 0 || idx >= size)
        {
            throw getEx;
        }

        return array[idx];
    }
   
};


int main()
{
    // //for random intigers;
    std::mt19937 mt{}; 

    std::cout << "Hello, World!\n";

    Stack<int>* intStack = new Stack<int>;

    //insert data
    for(int i{0}; i < 100; ++i)
    {
        intStack->push(mt());
    }
    
    std::cout << "-----------------------------------------------\n";

    // for(int i{0}; i < 100; ++i)
    // {
    //     std::cout << " \t Stack[" << i << "] = " << intStack->get(i) << "\n";   
    // }

    int item{};

    //retrive data
    for (int i{0}; i < 100; ++i)
    {
        item = intStack->pop();
        std::cout << "[pop]\t Stack[" << 99 - i << "] = " << item << "\n"; 
    }

    delete intStack;

    return 0;
}