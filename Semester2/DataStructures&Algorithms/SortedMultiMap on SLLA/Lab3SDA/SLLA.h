#pragma once
#include <vector>
#include <utility>
#include"SortedMultiMap.h"
template <class type>
class SLLA {
    friend class SortedMultiMap;
public:

    int capacity{};
    type* elems;
    int* next{};
    int head{};
    int firstEmpty{};
    int size = 0;


    SLLA() {

        this->capacity = 5;
        this->elems = new type[this->capacity];
        this->next = new int[this->capacity];
        this->head = -1;
        for (int i = 0; i < this->capacity; i++) {
            this->next[i] = i + 1;
        }
        this->next[this->capacity - 1] = -1;
        this->firstEmpty = 0;
    }

    ~SLLA() {


    }
};
