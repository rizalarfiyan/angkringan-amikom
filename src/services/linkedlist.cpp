#include "linkedlist.h"

OrderHistory::OrderHistory() : head(nullptr), tail(nullptr) {}

void OrderHistory::addOrder(const Order& order) {
    OrderNode* newNode = new OrderNode(order);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void OrderHistory::displayOrderHistory() const {
    if (head == nullptr) {
        cout << "Order history is empty." << endl;
    } else {
        cout << "Order History:" << endl;
        OrderNode* currentNode = head;
        while (currentNode != nullptr) {
            cout << "+-----------------------------+" << endl;
            cout << "| ORDER ID      : " << setw(17) << left << currentNode->order.orderId  << " |" << endl;
            cout << "| Username     : " << setw(17) << left << currentNode->order.user.username << " |" << endl;
            cout << "| Price    : $" << setw(16) << fixed << setprecision(2) << left << currentNode->order.totalPrice << " |" << endl;
            cout << "| Quantity : " << setw(17) << left << currentNode->order.quantity << " |" << endl;
            cout << "+-----------------------------+" << endl;
            
            cout << "Order ID: " << currentNode->order.orderId << endl;
            cout << "Username: " << currentNode->order.user.username << endl;
            cout << "Quantity: " << currentNode->order.quantity << endl;
            cout << "Price: $" << fixed << setprecision(2) << currentNode->order.totalPrice << endl;
            cout << endl;
            currentNode = currentNode->next;
        }
    }
}

OrderHistory::~OrderHistory() {
    OrderNode* currentNode = head;
    while (currentNode != nullptr) {
        OrderNode* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}