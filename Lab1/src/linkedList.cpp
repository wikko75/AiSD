#include <iostream>
#include <random> // for std::mt19937
#include <string>
#include <chrono>


class addException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "[Can not add data (wrong index provided)]\n";
  }
} addEx;


class removeException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "[Can not remove data at given index (wrong index or empty list)]\n";
  }
} removeEx;


class getException : public std::exception
{
   virtual const char* what() const throw()
  {
    return "[Can not retrive data at given index (wrong index or empty list)]\n";
  } 
} getEx;


template <class T>
class Node
{
    private:
    T data{};
    Node<T>* next{};

    public:
    Node<T>(const T& data)
    {
        this->data = data;
    }

    Node<T>* getNext()
    {
        return next;
    }
    
    void setNext(Node<T>* newNode)
    {
        next = newNode;
    }

    T getData()
    {
        return data;
    }
};

template <class T>
class LinkedList
{
    private:
    Node<T>* start{};
    int length{0};


    public:
    void add(const T& data)
    {

        Node<T>* currentNode = start;

        if(currentNode == nullptr)
        {
            currentNode = new Node<T>(data);
            setStartNode(currentNode);
            ++length;

            return;
        }
        
        while(currentNode->getNext() != nullptr)
        {
            currentNode = currentNode->getNext();
        }

        Node<T>* newNode = new Node<T>(data);

        currentNode->setNext(newNode);
        ++length;

        //std::cout << "Added data (at the end) DATA[" << data << "]\n";
        
    }
    
    void add(const T& data, int idx) noexcept(false)
    {
        if(idx < 0 || idx > length) 
        {
            throw addEx;
        }

        if(idx == length)
        {
            add(data); //call basic version(add to the end)
            return;
        }


        Node<T>* currentNode = start;
        Node<T>* addedNode = new Node<T>(data);
        
        if(idx == 0)   //to be changed wrong order should insert after first element not before//
        {
            addedNode->setNext(currentNode);
            setStartNode(addedNode);
            ++length;
            
            return;
        }

        for (int i{0}; i < idx-1; i++) //up to a left neighborn 
        {
            currentNode = currentNode->getNext();
        }
        
        addedNode->setNext(currentNode->getNext());     
        currentNode->setNext(addedNode);

        ++length;

        //std::cout << "Added data (at idx[" << idx << ") DATA[" << data << "]\n";
    }

    void remove(int idx) noexcept(false)
    {
        if(idx < 0 || idx >= length)
        {
            throw removeEx;
        }

        if(idx == 0)
        {
            Node<T>* nodeToDelete = get(0);
            setStartNode(nodeToDelete->getNext());
            delete nodeToDelete;
            --length;

            return;
        }

        Node<T>* previousNode = get(idx-1);
        Node<T>* nodeToDelete = previousNode->getNext();
        
        previousNode->setNext(nodeToDelete->getNext());
        
        --length;

        delete nodeToDelete;
    }

    void remove()
    {
        if(length <= 0)
        {
            return;
        }
        if (length == 1)
        {
            delete get(0);
            setStartNode(nullptr);
            --length;

            return;
        }

        delete get(length-1);               //node to delete
        get(length-2)->setNext(nullptr);    //previous node
        --length;
    }
    
    Node<T>* get(int idx) noexcept(false)
    {
        if(idx < 0 || idx >= length)
        {
            throw getEx;  //should be an exception but I'm lazy today...  EDIT: not anymore
        }

        Node<T>* currentNode = start;

        for (int i{0}; i < idx; ++i)
        {
            currentNode = currentNode->getNext();
        }
        
        return currentNode;

    }

    int size()
    {
        return length;
    }

    private:
    void setStartNode(Node<T>* node)
    {
        start = node;
    }

    void setSize(int size)
    {
        length = size;
    }

    public:
    /// @brief Merges two lists together. Stores result in firstList (first argument)
    /// @param firstList list secondList is added to
    /// @param secondList list being added to the firstList
    static void merge(LinkedList<T>* firstList, LinkedList<T>* secondList)
    {
        int lastNodeIdx = firstList->size() - 1;
        Node<T>* lastNodeOfFirstList = firstList->get(lastNodeIdx);
        lastNodeOfFirstList->setNext(secondList->get(0));
    
        int outListLength = firstList->size() + secondList->size();
        firstList->setSize(outListLength);
    }
};

int main()
{
    //for random intigers;
    std::mt19937 mt{}; 

     LinkedList<int>* intList = new LinkedList<int>();
     LinkedList<int>* intList2 = new LinkedList<int>();

     intList->add(11);
     intList2->add(22);

     LinkedList<int>::merge(intList, intList2);

     //test of merge
    for(int i{0}; i < intList->size(); ++i)
    {
        std::cout << "intList[" << i << "] = " << intList->get(i)->getData() << "\n";
    }

     intList->remove();
     intList->remove();
    

    //insert random integers 
    int i{0};
    while (i < 10000)
    {
        intList->add(mt());
        ++i;
    }


    for (int i{0}; i < intList->size() ; ++i)
    {
        //std::cout << "Data at index [" << i << "] = " << intList->get(i)->getData() << "\n";
    }



    //TESTS - time required to get an element
    //--------------------------------------------------------------------------------------------------------

    auto startTime = std::chrono::steady_clock::now();
    
    intList->get(9999);

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime);
    
    std::cout << "Retrieving 9999th element took\t\t    " << duration.count() << " milliseconds.\n\n";



    startTime = std::chrono::steady_clock::now();

    intList->get(4999);

    endTime = std::chrono::steady_clock::now();
    duration = std::chrono::duration<double, std::milli>(endTime - startTime);
    
    std::cout << "Retrieving 4999th element (middle one) took " << duration.count() << " milliseconds.\n\n";



    startTime = std::chrono::steady_clock::now();

    intList->get(500);

    endTime = std::chrono::steady_clock::now();
    duration = std::chrono::duration<double, std::milli>(endTime - startTime);
    
    std::cout << "Retrieving 500th element took\t\t    " << duration.count() << " milliseconds.\n\n";

    startTime = std::chrono::steady_clock::now();



    std::uniform_int_distribution idx{0, intList->size()-1};  //random index
    intList->get(idx(mt));

    endTime = std::chrono::steady_clock::now();
    duration = std::chrono::duration<double, std::milli>(endTime - startTime);
    
    std::cout << "Retrieving random element took\t\t    " << duration.count() << " milliseconds.\n";

    delete intList;
    delete intList2;

    return 0;
}