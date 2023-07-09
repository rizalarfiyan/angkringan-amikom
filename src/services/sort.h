#ifndef SORT_H
#define SORT_H


#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Sort {
public:
    static void bubble(vector<T>& items, bool (*compare)(const T&, const T&));
};

#include "sort.cpp"

#endif
