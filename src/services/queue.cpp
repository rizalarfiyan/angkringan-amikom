#include "queue.h"

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr) {}

template <typename T>
bool Queue<T>::isEmpty() {
    return front == nullptr;
}

template <typename T>
void Queue<T>::enqueue(const T& element) {
    Node* newNode = new Node(element);

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

template <typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue." << endl;
        return;
    }

    Node* temp = front;
    front = front->next;

    delete temp;

    if (isEmpty()) {
        rear = nullptr;
    }
}

template <typename T>
T Queue<T>::peek() {
    if (isEmpty()) {
        cout << "Queue is empty. No element to peek." << endl;
        return T();
    }

    return front->data;
}

template <typename T>
bool Queue<T>::isLast() {
	if (isEmpty()) {
		return false;
	}

	Node* current = front;
	while (current != nullptr) {
		if (current == rear) {
			return true;
		} else {
			return false;
		}
		current = current->next;
	}
	return false;
}