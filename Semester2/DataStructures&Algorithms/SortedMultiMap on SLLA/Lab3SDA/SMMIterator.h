
#pragma once

#include "SortedMultiMap.h"


class SMMIterator {
    friend class SortedMultiMap;
private:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    SMMIterator(const SortedMultiMap& map);

    int indexElem, indexValue;

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

    void nextKey();
};






