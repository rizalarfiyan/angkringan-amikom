#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template<typename T>
class Search {
public:
    template<typename Callback>
    static vector<T> fuzzy(const vector<T>& items, Callback callback, const string& searchQuery);
    
private:
    static bool isFuzzyMatch(const string& fieldValue, const string& searchQuery);
};

#include "search.cpp"

#endif
