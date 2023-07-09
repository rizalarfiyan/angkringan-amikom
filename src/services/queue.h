#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
struct Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue();
    bool isEmpty();
    void enqueue(const T& element);
    void dequeue();
    T peek();
};

#include "queue.cpp"

#endif
