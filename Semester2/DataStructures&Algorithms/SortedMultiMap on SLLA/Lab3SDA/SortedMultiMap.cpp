#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->r = r;
}

/*
void SortedMultiMap::add(TKey c, TValue v) {
    WC-O(n*n)
      BC-O(n)
      AC-O(n)
    
for (int i = 0; i < this->slla.capacity; i++)
{

    if (this->slla.elems[i].first == c)
    {
        if (slla.elems[i].second.size == 0)
        {
            int currentPos = this->slla.head, isHead = 1, prev = currentPos;
            if (this->slla.size > 0)
                while (this->r(this->slla.elems[currentPos].first, c) && currentPos != -1)
                {
                    prev = currentPos;
                    currentPos = this->slla.next[currentPos];
                    isHead = 0;
                }

            SLLA<TValue> values;
            values.addSLLA(v, 0, 0);
            pair<TKey, SLLA<TValue>>elem(c, values);
            this->slla.addSLLA(elem, prev, isHead);
        }
        else
        {
            this->slla.elems[i].second.addSLLA(v, 0, 0);
            this->slla.size++;
        }
        return;
    }
}

SLLA<TValue> values;
values.addSLLA(v, 0, 0);
pair<TKey, SLLA<TValue>>elem(c, values);

int currentPos = this->slla.head, isHead = 1, prev = 0;
if (this->slla.size > 0)
while (this->r(this->slla.elems[currentPos].first, c) && currentPos != -1)
{
    prev = currentPos;
    currentPos = this->slla.next[currentPos];
    isHead = 0;
}

this->slla.addSLLA(elem, prev, isHead);
}
*/


void expandValues(SLLA<TValue>* slla) {

    int oldCapacity = slla->capacity;
    slla->capacity *= 2;
    TValue* tempElems = new TValue[slla->capacity];
    int* tempNext = new int[slla->capacity];

    for (int i = oldCapacity; i < slla->capacity; i++) {
        tempNext[i] = i + 1;
    }
    tempNext[slla->capacity - 1] = -1;
    for (int i = 0; i < oldCapacity; i++) {
        tempElems[i] = slla->elems[i];
        tempNext[i] = slla->next[i];
    }
    delete[] slla->elems;
    delete[] slla->next;
    slla->elems = tempElems;
    slla->next = tempNext;
    slla->firstEmpty = oldCapacity;
    slla->next[slla->capacity - 1] = -1;
}

void expand(SLLA<pair<TKey, SLLA<TValue>>>* slla) {

    int oldCapacity = slla->capacity;
    slla->capacity *= 2;
    pair<TKey, SLLA<TValue>>* tempElems = new pair<TKey, SLLA<TValue>>[slla->capacity];
    int* tempNext = new int[slla->capacity];

    for (int i = oldCapacity; i < slla->capacity; i++) {
        tempNext[i] = i + 1;
    }
    tempNext[slla->capacity - 1] = -1;
    for (int i = 0; i < oldCapacity; i++) {
        tempElems[i] = slla->elems[i];
        tempNext[i] = slla->next[i];
    }
    delete[] slla->elems;
    delete[] slla->next;
    slla->elems = tempElems;
    slla->next = tempNext;
    slla->firstEmpty = oldCapacity;
    slla->next[slla->capacity - 1] = -1;
}

void SortedMultiMap::add(TKey c, TValue v) {
    /*WC-O(n*n)
      BC-O(n)
      AC-O(n)
    */
    for (int i = 0; i < this->slla.capacity; i++)
    {
        
        if (this->slla.elems[i].first == c)
        {
            if (slla.elems[i].second.size == 0)
            {
                int currentPos = this->slla.head, isHead = 1, prev = currentPos;
                if (this->slla.size > 0)
                    while (this->r(this->slla.elems[currentPos].first, c) && currentPos != -1)
                    {
                        prev = currentPos;
                        currentPos = this->slla.next[currentPos];
                        isHead = 0;
                    }

                SLLA<TValue> values;
                

                    int nextFE = -1;
                    if (values.firstEmpty < 0)expandValues(&values);

                    if (values.firstEmpty >= 0)
                        nextFE = values.next[values.firstEmpty];
                    values.elems[values.firstEmpty] = v;

                    if (values.size == 0)
                    {
                        values.next[values.firstEmpty] = -1;
                        values.head = values.firstEmpty;
                    }
                    else
                    {
                            values.next[values.firstEmpty] = values.next[0];
                            values.next[0] = values.firstEmpty;
                    }
                    values.firstEmpty = nextFE;
                    values.size++;
                //}



                pair<TKey, SLLA<TValue>>elem(c, values);
                

                    nextFE = -1;
                    if (slla.firstEmpty < 0)expand(&slla);

                    if (slla.firstEmpty >= 0)
                        nextFE = slla.next[slla.firstEmpty];
                    slla.elems[slla.firstEmpty] = elem;

                    if (slla.size == 0)
                    {
                        slla.next[slla.firstEmpty] = -1;
                        slla.head = slla.firstEmpty;
                    }
                    else
                    {
                        if (isHead == 1)
                        {
                            slla.next[slla.firstEmpty] = slla.head;
                            slla.head = slla.firstEmpty;
                        }
                        else
                        {
                            slla.next[slla.firstEmpty] = slla.next[prev];
                            slla.next[prev] = slla.firstEmpty;
                        }
                    }
                    slla.firstEmpty = nextFE;
                    slla.size++;
                //}

            }
            else
            {
                
                int nextFE = -1;
                if (slla.elems[i].second.firstEmpty < 0)expandValues(&slla.elems[i].second);

                if (slla.elems[i].second.firstEmpty >= 0)
                    nextFE = slla.elems[i].second.next[slla.elems[i].second.firstEmpty];
                slla.elems[i].second.elems[slla.elems[i].second.firstEmpty] = v;

                if (slla.elems[i].second.size == 0)
                {
                    slla.elems[i].second.next[slla.elems[i].second.firstEmpty] = -1;
                    slla.elems[i].second.head = slla.elems[i].second.firstEmpty;
                }
                else
                {
                    slla.elems[i].second.next[slla.elems[i].second.firstEmpty] = slla.elems[i].second.next[0];
                    slla.elems[i].second.next[0] = slla.elems[i].second.firstEmpty;
                }
                slla.elems[i].second.firstEmpty = nextFE;
                slla.elems[i].second.size++;

                this->slla.size++;
            }
            return;
        }
    }

    SLLA<TValue> values;
   
    int nextFE = -1;
    if (values.firstEmpty < 0)expandValues(&values);

    if (values.firstEmpty >= 0)
        nextFE = values.next[values.firstEmpty];
    values.elems[values.firstEmpty] = v;

    if (values.size == 0)
    {
        values.next[values.firstEmpty] = -1;
        values.head = values.firstEmpty;
    }
    else
    {
        values.next[values.firstEmpty] = values.next[0];
        values.next[0] = values.firstEmpty;
    }
    values.firstEmpty = nextFE;
    values.size++;

    pair<TKey, SLLA<TValue>>elem(c, values);

    int currentPos = this->slla.head, isHead = 1, prev = 0;
    if (this->slla.size > 0)
        while (this->r(this->slla.elems[currentPos].first, c) && currentPos != -1)
        {
            prev = currentPos;
            currentPos = this->slla.next[currentPos];
            isHead = 0;
        }

    
    nextFE = -1;
    if (slla.firstEmpty < 0)expand(&slla);

    if (slla.firstEmpty >= 0)
        nextFE = slla.next[slla.firstEmpty];
    slla.elems[slla.firstEmpty] = elem;

    if (slla.size == 0)
    {
        slla.next[slla.firstEmpty] = -1;
        slla.head = slla.firstEmpty;
    }
    else
    {
        if (isHead == 1)
        {
            slla.next[slla.firstEmpty] = slla.head;
            slla.head = slla.firstEmpty;
        }
        else
        {
            slla.next[slla.firstEmpty] = slla.next[prev];
            slla.next[prev] = slla.firstEmpty;
        }
    }
    slla.firstEmpty = nextFE;
    slla.size++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    /*WC-O(n*n)
     BC-O(n)
     AC-O(n)
   */
    vector<TValue> values;
    int current = slla.head;
    bool ok = false;
    
    for (int i = 0; i < this->slla.capacity; i++) {
        if (this->slla.elems[i].first == c && this->slla.elems[i].second.size > 0)
        {
            current = i;
            ok = true;
            break;
        }
    }
    
    if (!ok)
        return values;
    
    int currentValue = this->slla.elems[current].second.head;
    while (currentValue != -1) {
        values.push_back(this->slla.elems[current].second.elems[currentValue]);
        currentValue = this->slla.elems[current].second.next[currentValue];
    }
    return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    /*WC-O(n)
     BC-O(1)
     AC-O(n/2)
   */
    vector<TValue> values = this->search(c);
    SLLA<TValue> value;
    //value.addSLLA(v, 0, 0);

    int nextFE = -1;
    if (value.firstEmpty < 0)expandValues(&value);

    if (value.firstEmpty >= 0)
        nextFE = value.next[value.firstEmpty];
    value.elems[value.firstEmpty] = v;

    if (value.size == 0)
    {
        value.next[value.firstEmpty] = -1;
        value.head = value.firstEmpty;
    }
    else
    {
        value.next[value.firstEmpty] = value.next[0];
        value.next[0] = value.firstEmpty;
    }
    value.firstEmpty = nextFE;
    value.size++;

    pair<TKey, SLLA<TValue>>elem(c, value);

    if (values.size() == 1)
    {
        bool ok = false;
        for (int i = 0; i < values.size(); ++i)
            if (v == values[i])
                ok = true;
        if (ok)
        {
            bool okk = true;
            int current = this->slla.head;
            int prev = -1;

            while (current != -1 && this->slla.elems[current].first != elem.first) {
                prev = current;
                current = this->slla.next[current];
            }
            if (current != -1)
            {
                if (current == this->slla.head) {
                    this->slla.head = this->slla.next[slla.head];

                }
                else {
                    this->slla.next[prev] = this->slla.next[current];
                }
                this->slla.next[current] = this->slla.firstEmpty;
                this->slla.firstEmpty = current;
            }
            else {
                okk = false;
            }
            if (okk) {
                this->slla.size--;
                return true;
            }
        }
        
    }
    else {
        for (int i = 0; i < this->slla.capacity; i++) {
            if (this->slla.elems[i].first == c) {
                bool ok = true;
                int current = this->slla.elems[i].second.head;
                int prev = -1;
                while (current != -1 && this->slla.elems[i].second.elems[current] != v) {
                    prev = current;
                    current = this->slla.elems[i].second.next[current];
                }
                if (current != -1)
                {
                    if (current == this->slla.elems[i].second.head) {
                        this->slla.elems[i].second.head = this->slla.elems[i].second.next[slla.elems[i].second.head];

                    }
                    else {
                        this->slla.elems[i].second.next[prev] = this->slla.elems[i].second.next[current];
                    }
                    this->slla.elems[i].second.next[current] = this->slla.elems[i].second.firstEmpty;
                    this->slla.elems[i].second.firstEmpty = current;
                }
                else {

                    ok = false;
                }
                if (ok)
                    this->slla.elems[i].second.size--;


                if (ok) {
                    this->slla.size--;
                    return true;
                }
            }
        }
    }
    return false;
}


int SortedMultiMap::size() const {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */

    return this->slla.size;
}

bool SortedMultiMap::isEmpty() const {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    return this->slla.size == 0;
}

SMMIterator SortedMultiMap::iterator() const {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    return SMMIterator(*this);
}

TValue SortedMultiMap::mostFrequent() const
{//returns the TValue that appears most frequently in the SortedMultiMap.
    //If multiple TValues appear most frequently, returns any of them. 
//if the SortedMultiMap is empty, the operation returns NULL_TVALUE
    /*BC-O(n*n)
      WC-O(n*n)
      AG-O(n*n)*/
    if (this->isEmpty() == true)return NULL_TVALUE;
    else {
        TValue elements[100];
        int frequency[100];
        int cnt = 0;
        int index = 0;
        int maxFrequency = 0;
        int indexMaxFrequency = 0;
        int indexElem = this->slla.head;
        int indexValue = this->slla.elems[indexElem].second.head;

        while (!(indexValue == -1 || indexElem == -1))
        {
            //calculate frequencies
            int ok = 0;
            for (int i = 0; i < 100; i++)
            {
                if (elements[i] == this->slla.elems[indexElem].second.elems[indexValue])
                {
                    ok = 1;
                    index = i;
                }
            }
            if (ok == 0)
            {
                frequency[cnt]++;
                elements[cnt] = this->slla.elems[indexElem].second.elems[indexValue];
                if (maxFrequency < frequency[index])
                {
                    maxFrequency = frequency[index];
                    indexMaxFrequency = index;
                }

                cnt++;
            }
            else
            {
                frequency[index]++;
                if (maxFrequency < frequency[index])
                {
                    maxFrequency = frequency[index];
                    indexMaxFrequency = index;
                }
            }

            //next element
            if (this->slla.elems[indexElem].second.next[indexValue] == -1) {
                indexElem = this->slla.next[indexElem];
                indexValue = this->slla.elems[indexElem].second.head;
            }
            else {
                indexValue = this->slla.elems[indexElem].second.next[indexValue];
            }
        }
        
        return elements[indexMaxFrequency];
    }
    
}

SortedMultiMap::~SortedMultiMap() {
    /*WC-O(n)
     BC-O(n)
     AC-O(n)
   */
    for (int i = 0; i < this->slla.capacity; i++) {
        delete[] this->slla.elems[i].second.elems;
        delete[] this->slla.elems[i].second.next;
    }
    delete[] this->slla.elems;
    delete[] this->slla.next;
}
