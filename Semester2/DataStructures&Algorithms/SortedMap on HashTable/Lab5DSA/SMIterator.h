
#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
    friend class SortedMap;
private:
    const SortedMap& map;
    SMIterator(const SortedMap& mapionar);

    //TODO - Representation
    SortedMap::listT  elementsList;
    SortedMap::nodeT * elem = nullptr;

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};



