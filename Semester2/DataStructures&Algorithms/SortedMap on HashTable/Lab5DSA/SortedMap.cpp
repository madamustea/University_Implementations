
#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SortedMap::SortedMap(Relation r) {
    /*BC-O(1)
      WC-O(n)
      AC-O(n)
    */

    hashTable = new listT[hashTableSize];
    for(int i=0;i<hashTableSize;i++)
    {
        hashTable[i].size = 0;
        hashTable[i].head = nullptr;
        hashTable[i].tail = nullptr;
    }
    this->r = r;
}

TValue SortedMap::add(TKey k, TValue v) {
    /*BC-O(1)
      WC-O(m)
      AC-O(m)
    */
    int position = abs(k % hashTableSize);
   

    TElem element;
    element.first = k;
    element.second = v;

    //add to list

    //create new node
    auto * newElement = new nodeT;
    newElement->elem = element;
    newElement->next = nullptr;

    //add node to hashTable[position] which is named here h for simplicity
    listT * h = &hashTable[position];

    //if hashTable[position] is empty
    if(h->head == nullptr)
    {
        h->head = newElement;
        h->tail = h->head;
    }
    //if not empty
    else
    {
        nodeT * current = h->head;
        
        if(current->elem.first == k)
        {
            TValue returnValue = current->elem.second;
            current->elem.second = v;
            return returnValue;
        }
         
        while(current)
        {
            if(current->elem.first == k )
            {
                TValue returnValue = current->elem.second;
                current->elem.second = v;
               
                return returnValue;
            }
            current = current->next;
        }
        

        //if added as head
                                
        if(r(k,h->head->elem.first))
        {
            newElement->next = h->head;
            h->head = newElement;
        }
        else
        {
            //if added after tail
            if(r(h->tail->elem.first,k))
            {
                h->tail->next = newElement;
                h->tail = newElement;
            }
            //if added between
            else
            {
                current = h->head;
                nodeT * prev = current;
                while(current->next && !r(k,current->elem.first))
                {
                    prev = current;
                    current = current->next;
                }
                newElement->next = current;
                prev->next = newElement;
            }
        }
    }
    
    h->size++;
    sortedMapSize++;



    return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
    /*BC-O(1)
      WC-O(n*m)
      AC-O(n*m)
    */
    for (int i = 0; i < hashTableSize; ++i)
    {
       
        listT * h = &hashTable[i];
        nodeT * current = h->head;

        if(current)
        {
            while(current)
            {
                if(current->elem.first == k)
                    return current->elem.second;
                current = current->next;
            }
            
        }
        
    }
    
    return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    /*BC-O(1)
      WC-O(n*m)
      AC-O(n*m)
    */
    
    if(search(k) == NULL_TVALUE)
        return NULL_TVALUE;

    for(int i=0; i<hashTableSize;i++)
    {
        while(!hashTable[i].head)
            i++;

        
        TValue returnValue;
        nodeT * head = hashTable[i].head;
        nodeT * prev = hashTable[i].head;

        //if key is head
        if(head->elem.first == k)
        {
            //update head
            returnValue = hashTable[i].head->elem.second;
            hashTable[i].head = hashTable[i].head->next;
            head->next = nullptr;
            //delete
            sortedMapSize--;
            hashTable[i].size--;
            free(head);
            //return value
            return returnValue;
        }
        //if key is not head, search all keys in list
        while(head->next && head->elem.first!=k)
        {
            prev = head;
            head = head->next;
        }
        //if key found
        if(head->elem.first==k)
        {
            //if it is tail, update tail
            if(head->elem.first == hashTable[i].tail->elem.first)
                hashTable[i].tail = prev;
            //delete
            prev->next = head->next;
            returnValue = head->elem.second;
            free(head);
            //return value
            hashTable[i].size--;
            sortedMapSize--;
            return returnValue;
        }
        //go to next list
    }
}

int SortedMap::size() const {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
    return sortedMapSize;
}

bool SortedMap::isEmpty() const {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
    return !size();
}

void SortedMap::replace(TKey k, TValue oldValue, TValue newValue)
{/*BC-O(1)
      WC-O(m)
      AC-O(m)
 */
    if (this->search(k) == NULL_TVALUE)return;

    int position = abs(k % hashTableSize);
    TElem element;
    element.first = k;
    element.second = newValue;

    auto* newElement = new nodeT;
    newElement->elem = element;
    newElement->next = nullptr;

    listT* h = &hashTable[position];

   
   
    nodeT* current = h->head;

    if (current->elem.first == k && current->elem.second==oldValue)
    {
            
        current->elem.second = newValue;
        return;
    }

    while (current)
    {
        if (current->elem.first == k && current->elem.second==oldValue)
        {
            TValue returnValue = current->elem.second;
            current->elem.second = newValue;

            return;
        }
        current = current->next;
    }

}

SMIterator SortedMap::iterator() const {
    /*BC-O(1)
      WC-O(1)
      AC-O(1)
    */
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    /*BC-O(n*m)
      WC-O(n*m)
      AC-O(n*m)
    */
    
    for(int i=0; i<hashTableSize;i++)
    {
        nodeT * temporaryNode;
        while(hashTable[i].head)
        {
            temporaryNode = hashTable[i].head;
            hashTable[i].head = hashTable[i].head->next;
            free(temporaryNode);
        }
    }
    free(hashTable);
}


