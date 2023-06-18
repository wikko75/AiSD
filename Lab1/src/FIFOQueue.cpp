#include <iostream>
#include <exception>
#include <random> // for std::mt19937


class dequeueException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "[No data in queue, nothing to delete]\n";
  }
} dequeueEx;


class getException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "[Can not retrive data at given index (wrong index or empty queue)]\n";
  }
} getEx;


template<class T>
class Queue
{
    private:
    T* array{};
    T* swapArray{};
    int size{};

    public:
    void enqueue(T data)
    {
        if(size < 0)
        {
            return;
        }

        if(size == 0)
        {
            array = new T[1];

            array[0] = data;

            ++size;

            return;
        }

        swapArray = new T[size];

        for (int i{0}; i < size; ++i)
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
        ++size;

        delete[] swapArray;
    }

    T dequeue() noexcept(false)
    {
        if (size == 0)
        {
           throw dequeueEx;
        }

        T firstElement = array[0];
        swapArray = new T[size - 1];

        for (int i{0}; i < size-1; ++i)
        {
            swapArray[i] = array[i+1];
        }

        delete[] array;
        array = new T[size - 1];

        for (int i{0}; i < size- 1; ++i)
        {
            array[i] = swapArray[i];
        }

        --size;
        delete[] swapArray;

        return firstElement;
    }

    T get(int idx) const noexcept(false)
    {
        if(idx < 0 || idx >= size)
        {
           throw  getEx; 
        }

        return array[idx];
    }
};

int main()
{
    std::mt19937 mt{}; //for random integers

    Queue<int>* intQueue = new Queue<int>;

    int data{};

    //insert data
    for(int i{0}; i < 100; ++i)
    {
        data = mt();
        intQueue->enqueue(data);
        std::cout << "[enqueue]\t Queue[" << i << "] = " << data << "\n";

    }

    int item{};

    std::cout << "--------------------------------------------------------------\n";

    //retrive data
    for(int i{0}; i < 100; ++i)
    {
        item = intQueue->dequeue();
        std::cout << "[dequeue]\t Queue[" << i << "] = " << item << "\n"; 

    }

    delete intQueue;

    return 0;
}