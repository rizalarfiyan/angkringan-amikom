#include "stack.h"

template <typename T>
bool Stack<T>::isEmpty() const {
    return stack.empty();
}

template <typename T>
void Stack<T>::push(const T& element) {
    stack.push_back(element);
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw out_of_range("Stack is empty");
    }

    T topElement = stack.back();
    stack.pop_back();
    return topElement;
}

template <typename T>
T& Stack<T>::top() {
    if (isEmpty()) {
        throw out_of_range("Stack is empty");
    }

    return stack.back();
}

template <typename T>
size_t Stack<T>::size() const {
    return stack.size();
}
