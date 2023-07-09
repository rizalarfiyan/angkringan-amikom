#ifndef MODELS_H
#define MODELS_H

#include <string>
#include "services/stack.h"
using namespace std;

struct FoodItem {
    int id;
    string name;
    double price;

	int quantity;
};

struct User {
    string username;
    string password;
    Stack<FoodItem> cart;
};

struct Order {
    int orderId;
    double totalPrice;
	Stack<FoodItem> items;
    User user;
};

struct OrderNode {
    Order order;
    OrderNode* next;

    OrderNode(const Order& order) : order(order), next(nullptr) {}
};

#endif
