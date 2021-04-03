#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include<iostream>
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    indexElem = this->map.slla.head;
    indexValue = this->map.slla.elems[indexElem].second.head;
}

void SMMIterator::first() {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    indexElem = this->map.slla.head;
    indexValue = this->map.slla.elems[indexElem].second.head;
}

void SMMIterator::next() {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    if (valid()) {
        if (this->map.slla.elems[indexElem].second.next[indexValue] == -1) {
            indexElem = this->map.slla.next[indexElem];
            indexValue = this->map.slla.elems[indexElem].second.head;
        }
        else {
            indexValue = this->map.slla.elems[indexElem].second.next[indexValue];
        }
    }
    else throw std::exception();
}
void SMMIterator::nextKey() {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    if (valid()) {
        indexElem = this->map.slla.next[indexElem];
        indexValue = this->map.slla.elems[indexElem].second.head;
    }
    else throw std::exception();
}
bool SMMIterator::valid() const {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    if (indexValue == -1 || indexElem == -1)
        return false;
    return true;
}
TElem SMMIterator::getCurrent() const {
    /*WC-O(1)
     BC-O(1)
     AC-O(1)
   */
    if (valid()) {
        pair<TKey, TValue> pair(this->map.slla.elems[indexElem].first, this->map.slla.elems[indexElem].second.elems[indexValue]);
        return pair;
    }
    else throw std::exception();
}


