#include <iostream>
#include <chrono>
#include <random> // for std::mt19937

template <class T>
class Node
{
    private:
    T data{};
    Node<T>* next{};
    Node<T>* previous{};

    public:
    Node<T>(const T& data)
    {
        this->data = data;
    }

    Node<T>* getNext()
    {
        return next;
    }

    Node<T>* getPrevious()
    {
        return previous;
    }

    void setNext(Node<T>* newNode)
    {
        next = newNode;
    }

    void setPrevious(Node<T>* newNode)
    {
        previous = newNode;
    }

    T getData()
    {
        return this->data;
    }
};

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
class DoubleCircularLinkedList
{
    private:
    Node<T>* start{};
    Node<T>* last{};
    int length{0};

    public:
    void add(const T& data)
    {

        Node<T>* currentNode = start;

        if(currentNode == nullptr)
        {
            currentNode = new Node<T>(data);
            setStartNode(currentNode);
            currentNode->setNext(start);
            setLastNode(currentNode);
            currentNode->setPrevious(last);
            ++length;

            return;
        }
        
        while(currentNode->getNext() != nullptr)
        {   
            if(currentNode->getNext() == start)
            {
                Node<T>* newNode = new Node<T>(data);

                currentNode->setNext(newNode);
                newNode->setPrevious(currentNode);
                setLastNode(newNode);
                newNode->setNext(start);

                ++length;
                return;
            }

            currentNode = currentNode->getNext();
        }

        Node<T>* newNode = new Node<T>(data);

        currentNode->setNext(newNode);
        newNode->setPrevious(currentNode);
        setLastNode(newNode);
        newNode->setNext(start);

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
        {                                                               //to be changed
            Node<T>* newNode = new Node<T>(data);

            newNode->setPrevious(getLastNode());
            newNode->setNext(start);
            start->setPrevious(newNode);
            (newNode->getPrevious())->setNext(newNode);
            setLastNode(newNode);

            ++length;

            return;
        }

        if(idx <= length/2)
        {
            Node<T>* currentNode = start;
            Node<T>* addedNode = new Node<T>(data);
        
            if(idx == 0)        //to be changed, wrong order, should insert after first element not before//
            {
                addedNode->setNext(start);
                start->setPrevious(addedNode);
                addedNode->setPrevious(last);
                last->setNext(addedNode);
                setStartNode(addedNode);
                ++length;
            
                return;
            }

            for (int i{0}; i < idx-1; ++i) //up to a left neighborn 
            {
                currentNode = currentNode->getNext();
            }
        
            addedNode->setNext(currentNode->getNext());
            addedNode->setPrevious(currentNode);     
            currentNode->setNext(addedNode);

            ++length;

            //std::cout << "Added data (at idx[" << idx << ") DATA[" << data << "]\n";
        }
        else
        {
            Node<T>* currentNode = last;
            Node<T>* addedNode = new Node<T>(data);
            
            for (int i{length-1}; i > idx+1; --i) //up to a right neighborn 
            {
                currentNode = currentNode->getPrevious();
            }

            addedNode->setNext(currentNode);
            addedNode->setPrevious(currentNode->getPrevious());
            (addedNode->getPrevious())->setNext(addedNode);

            ++length;

            //std::cout << "Added data (at idx[" << idx << ") DATA[" << data << "]\n"
        }
    }

    void remove(int idx) noexcept(false)
    {
        if(idx < 0 || idx >= length)
        {
            throw removeEx;
        }

        if(idx == 0)
        {
            Node<T>* nodeToDelete = start;
            setStartNode(nodeToDelete->getNext());
            start->setPrevious(last);
            last->setNext(start);

            --length;

            delete nodeToDelete;

            return;
        }

        Node<T>* previousNode = get(idx-1);
        Node<T>* nodeToDelete = previousNode->getNext();
        
        previousNode->setNext(nodeToDelete->getNext());
        (nodeToDelete->getNext())->setPrevious(previousNode);
        //setLastNode()
        if(nodeToDelete == last)
        {
            setLastNode(nodeToDelete->getPrevious());
            last->getNext()->setPrevious(last);
        }

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
            delete start;;
            setStartNode(nullptr);
            setLastNode(nullptr);

            --length;
            return;
        }

        last->getPrevious()->setNext(start);
        start->setPrevious(last->getPrevious());
        delete last;
        setLastNode(start->getPrevious());
        --length;
    }
    
    Node<T>* get(int idx) noexcept(false)
    {
        if(idx < 0 || idx >= length)
        {
            throw getEx;  //should be an exception but I'm lazy today...  EDIT: not anymore
        }


        if(idx < length/2)
        {
            Node<T>* currentNode = start;

            for (int i{0}; i < idx; ++i)
            {
                currentNode = currentNode->getNext();
            }
        
            return currentNode;
        }
    
        //if otherwise: idx >= length/2:
        Node<T>* currentNode = last;

        for (int i{length-1}; i > idx; --i)
        {
            currentNode = currentNode->getPrevious();
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

    void setLastNode(Node<T>* node)
    {
        last = node;
    }

    Node<T>* getLastNode()
    {
        return last;
    }

    void setSize(int size)
    {
        length = size;
    }

    public:
    /// @brief Merges two lists together. Stores result in firstList (first argument)
    ///        (in progress right now stores result in both but on different idx xd)
    /// @param firstList list secondList is added to
    /// @param secondList list being added to the firstList
    static void merge(DoubleCircularLinkedList<T>* firstList, DoubleCircularLinkedList<T>* secondList)
    {
        int lastNodeIdx = firstList->size() - 1;
        Node<T>* lastNodeOfFirstList = firstList->last;
        
        lastNodeOfFirstList->setNext(secondList->start);
        firstList->start->setPrevious(secondList->last);
        secondList->last->setNext(firstList->start);
        secondList->start->setPrevious(lastNodeOfFirstList);
    
        int outListLength = firstList->size() + secondList->size();
        firstList->setSize(outListLength);
        firstList->setLastNode(secondList->last);
    }
};


int main()
{
    //for random intigers;
    std::mt19937 mt{}; 

    DoubleCircularLinkedList<int>* intList = new DoubleCircularLinkedList<int>();
    DoubleCircularLinkedList<int>* intList2 = new DoubleCircularLinkedList<int>();

    intList->add(55);
    intList->add(11);
    intList2->add(100);
    intList2->add(99);

    DoubleCircularLinkedList<int>::merge(intList, intList2);

    //test of merge
    for(int i{0}; i < intList->size(); ++i)
    {
        std::cout << "intList[" << i << "] = " << intList->get(i)->getData() << "\n";
    }


    intList->remove();
    intList->remove();
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

    //TESTS - time required to get element
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