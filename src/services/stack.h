#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;


template <typename T>
class Stack {
private:
    vector<T> stack;

public:
    bool isEmpty() const;
    void push(const T& element);
    T pop();
    T& top();
    size_t size() const;
};

#include "stack.cpp"

#endif