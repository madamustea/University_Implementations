#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
    /*BC-O(n*m)
      WC-O(n*m)
      AC-O(n*m)
    */
    elementsList.head=nullptr;
    elementsList.tail=nullptr;
    
    int i = 0;
    SortedMap::listT currentList;//elementsList,
   
    for(i = 0; i<m.hashTableSize; i++)
    {
        currentList = m.hashTable[i];
        //if there is a list
        if(currentList.head)
        {
            //secondList = currentList;
            SortedMap::nodeT *currentNodeList = currentList.head;
            while(currentNodeList)
            {
                //create new node
                auto *currentNode = new SortedMap::nodeT;
                TElem x;
                x.first = currentNodeList->elem.first;
                x.second = currentNodeList->elem.second;
                currentNode->elem = x;
                currentNode->next = nullptr;

                if(elementsList.head == nullptr)
                {
                    elementsList.head = currentNode;
                    elementsList.tail = currentNode;
                }
                //if added as head
                else if(m.r(currentNode->elem.first , elementsList.head->elem.first))
                {
                    currentNode->next = elementsList.head;
                    elementsList.head = currentNode;
                }
                else
                {
                    //if added after tail
                    if(m.r(elementsList.tail->elem.first,currentNode->elem.first))
                    {
                        elementsList.tail->next = currentNode;
                        elementsList.tail = currentNode;
                        currentNode->next = nullptr;
                    }
                        //if added between
                    else
                    {
                        SortedMap::nodeT * current = elementsList.head;
                        SortedMap::nodeT * prev = current;
                        while(current->next && m.r(current->elem.first,currentNode->elem.first))
                        {
                            prev = current;
                            current = current->next;
                        }
                        currentNode->next = current;
                        prev->next = currentNode;
                    }
                }
                currentNodeList = currentNodeList->next;
            }
        }
        elementsList.size +=currentList.size;
    }

    
    elem = elementsList.head;
}

void SMIterator::first() {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
    
    elem = elementsList.head;
}

void SMIterator::next() {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
   
    if (valid()) {
        elem = elem->next;
    }
    else throw std::exception();
}

bool SMIterator::valid() const {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
   
    if(elem != nullptr)
        return true;
    else return false;
}

TElem SMIterator::getCurrent() const {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
    
    if(valid()){
        return elem->elem;
    }
    else throw std::exception();
}


