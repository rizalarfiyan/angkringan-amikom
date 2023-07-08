#ifndef MODELS_H
#define MODELS_H

#include <string>
#include "services/stack.h"
using namespace std;

struct FoodItem {
    int id;
    string name;
    double price;
};

struct User {
    string username;
    string password;
    Stack<FoodItem> cart;
};

struct Order {
    int orderId, quantity;
    double totalPrice;
    User user;
};

struct OrderNode {
    Order order;
    OrderNode* next;

    OrderNode(const Order& order) : order(order), next(nullptr) {}
};

#endif
