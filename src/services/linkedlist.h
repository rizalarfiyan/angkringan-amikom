#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include "../models.h"
#include "../utils.h"
using namespace std;

class OrderHistory {
private:
    OrderNode* head;
    OrderNode* tail;

public:
    OrderHistory();
    void addOrder(const Order& order);
    void displayOrderHistory() const;
    ~OrderHistory();
};

#include "linkedlist.cpp"

#endif