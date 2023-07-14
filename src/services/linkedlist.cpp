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
		cout << "+------------------------------------------------+" << endl;
		cout << "|             Order history is empty!            |" << endl;
		cout << "+------------------------------------------------+" << endl;
		return;
    }

	cout << "+------------------------------------------------+" << endl;
	cout << "|                 Order history:                 |" << endl;
	cout << "+------------------------------------------------+" << endl;
	OrderNode* currentNode = head;
	while (currentNode != nullptr) {
		cout << "+------------------------------------------------+" << endl;
		cout << "| Order ID : " << setw(36) << left << currentNode->order.orderId << "|" << endl;
		cout << "| Username : " << setw(36) << left << currentNode->order.user.username << "|" << endl;
		cout << "| Price    : " << setw(36) << left << formatCurrency(currentNode->order.totalPrice) << "|" << endl;

		if (!currentNode->order.items.isEmpty()) {
			cout << "| Items    : " << setw(36) << left << " " << "|" << endl;
		}

		while (!currentNode->order.items.isEmpty()) {
			FoodItem currentItem = currentNode->order.items.top();
			string itemName = currentItem.name + " (x" + to_string(currentItem.quantity) + ")";
			cout << "|    - " << setw(42) << left << itemName << "|" << endl;
			currentNode->order.items.pop();
		}

		cout << "+------------------------------------------------+" << endl;
		currentNode = currentNode->next;
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