#include <iostream>
#include <string>
#include <algorithm>
#include <random> // Include the random library
#include <cstdlib> // Include the cstdlib header for the system() function
#include <iomanip>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For UNIX-based systems (Linux, macOS)
#endif
}


template <typename T>
class Stack {
private:
    vector<T> stack;

public:
    // Check if the stack is empty
    bool isEmpty() const {
        return stack.empty();
    }

    // Push an element onto the stack
    void push(const T& element) {
        stack.push_back(element);
    }

    // Remove and return the top element from the stack
    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }

        T topElement = stack.back();
        stack.pop_back();
        return topElement;
    }

    // Return the top element of the stack without removing it
    T& top() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }

        return stack.back();
    }

    // Return the size of the stack
    size_t size() const {
        return stack.size();
    }
};

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
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Elements in the queue: ";
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void enqueue(const T& element) {
        Node* newNode = new Node(element);

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
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

    T peek() {
        if (isEmpty()) {
            cout << "Queue is empty. No element to peek." << endl;
            return T();
        }

        return front->data;
    }
};

// Struct to represent a food item
struct FoodItem {
    int id;
    string name;
    double price;
};

// Struct to represent a user
struct User {
    string username;
    string password;
    Stack<FoodItem> cart;
};

// Struct to represent an order
struct Order {
    int orderId, quantity;
    User user;
};

// Node struct for the linked list
struct OrderNode {
    Order order;
    OrderNode* next;

    OrderNode(const Order& order) : order(order), next(nullptr) {}
};

// Linked list to store order history
class OrderHistory {
private:
    OrderNode* head;
    OrderNode* tail;

public:
    OrderHistory() : head(nullptr), tail(nullptr) {}

    void addOrder(const Order& order) {
        OrderNode* newNode = new OrderNode(order);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void displayOrderHistory() const {
        if (head == nullptr) {
            cout << "Order history is empty." << endl;
        } else {
            cout << "Order History:" << endl;
            OrderNode* currentNode = head;
            while (currentNode != nullptr) {
                cout << "Order ID: " << currentNode->order.orderId << endl;
                cout << "Username: " << currentNode->order.user.username << endl;
                cout << "Quantity: " << currentNode->order.quantity << endl;
                cout << endl;
                currentNode = currentNode->next;
            }
        }
    }

    ~OrderHistory() {
        OrderNode* currentNode = head;
        while (currentNode != nullptr) {
            OrderNode* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }
};


// Comparator function for sorting food items by price in ascending order
bool compareByPrice(const FoodItem& item1, const FoodItem& item2) {
    return item1.price < item2.price;
}

// Function to add a food item to the cart
void addToCart(User* user, FoodItem& foodItem) {
    FoodItem newItem = foodItem;  // Create a copy of the FoodItem object
    user->cart.push(newItem);     // Push the new item to the cart
    cout << "-- Food item added to the cart! --" << endl;
}

// Function to process an order
void processOrder(User* user, Order order) {
    cout << "Processing Order ID: " << order.orderId << endl;
    cout << "Username: " << order.user.username << endl;
    cout << "Password: " << order.user.password << endl;

    // Process the items in the cart
    double totalPrice = 0.0;
    cout << "Cart Contents:" << endl;
    while (!order.user.cart.isEmpty()) {
        FoodItem currentItem = order.user.cart.top();
        cout << "ID: " << currentItem.id << endl;
        cout << "Name: " << currentItem.name << endl;
        cout << "Price: $" << currentItem.price << endl;
        cout << "Quantity: " << order.quantity << endl;
        totalPrice += (currentItem.price * order.quantity);
        cout << endl;
        order.user.cart.pop();
    }

    cout << "Total Price: $" << totalPrice << endl;
    cout << "-- Order processed successfully! --" << endl;

    user->cart = Stack<FoodItem>(); // Clear the cart
}



// Function to generate a random order ID
int generateRandomOrderId() {
    random_device rd; // Obtain a random seed from the operating system
    mt19937 gen(rd()); // Initialize the random number generator
    uniform_int_distribution<> dis(1000, 9999); // Define the range of order IDs
    return dis(gen); // Generate a random order ID
}


// Display the available food items
void displayAvailableFoodItems(const vector<FoodItem>& foodItems) {
    clearScreen(); // Clear the terminal screen
    cout << ".-----------------------." << endl;
    cout << "| Available Food Items: |" << endl;
    cout << "'-----------------------'" << endl;
    for (const auto& foodItem : foodItems) {
        cout << "+-----------------------------+" << endl;
        cout << "| ID    : " << setw(20) << left << foodItem.id << "|" << endl;
        cout << "| Name  : " << setw(20) << left << foodItem.name << "|" << endl;
        cout << "| Price : " << setw(20) << left << fixed << setprecision(2) << foodItem.price << "|" << endl;
        cout << "+-----------------------------+" << endl;

    }
}

// Display the order history
void displayOrderHistory(const OrderHistory& orderHistory) {
    orderHistory.displayOrderHistory();
}

// Function to search for a food item by name
int searchFoodItem(const vector<FoodItem>& foodItems, const string& itemName) {
    for (size_t i = 0; i < foodItems.size(); ++i) {
        if (foodItems[i].name == itemName) {
            return static_cast<int>(i);
        }
    }
    return -1; // Return -1 if the item is not found
}

// Function to handle user's choice
void handleUserChoice(char choice, User *user, vector<FoodItem>& availableFoodItems, Queue<Order>* orderQueue, OrderHistory* orderHistory) {
    switch (choice) {
        case '1': {
            displayAvailableFoodItems(availableFoodItems);
            break;
        }
        case '2': {
            displayAvailableFoodItems(availableFoodItems);
            // Prompt the user to select a food item
            int selectedItemId;
            cout << "--------------------------------------------" << endl;
            cout << "Eɴᴛᴇʀ ᴛʜᴇ ғᴏᴏᴅ Food ID ᴛᴏ ᴀᴅᴅ ᴛᴏ ᴛʜᴇ ᴄᴀʀᴛ " << endl;
            cout << "--------------------------------------------" << endl;
            cout << "Food ID: ";
            cin >> selectedItemId;

            // Find the selected food item in the available food items list
            FoodItem* selectedFoodItem = nullptr;
            for (auto& foodItem : availableFoodItems) {
                if (foodItem.id == selectedItemId) {
                    selectedFoodItem = &foodItem;
                    break;
                }
            }

            // Add the selected food item to the user's cart
            if (selectedFoodItem != nullptr) {
                clearScreen(); // Clear the terminal screen
                addToCart(user, *selectedFoodItem);

                // Prompt the user for the quantity
                int quantity;
                cout << "Enter the quantity: ";
                cin >> quantity;

                // Create an order and enqueue it for processing
                Order order;
                order.orderId = -1; // Temporary order ID, will be assigned later
                order.user = *user;
                order.quantity = quantity;
                orderQueue->enqueue(order);

                cout << "-- Order placed successfully! --" << endl;
            } else {
                clearScreen(); // Clear the terminal screen
                cout << endl << "-- Invalid food item ID. Please try again. --" << endl << endl;
            }
            break;
        }
        case '3': {
            clearScreen(); // Clear the terminal screen
            cout << "Cart Contents:" << endl;
            // create temp cart var
            Stack<FoodItem> tempCart = user->cart;

            if (tempCart.isEmpty()) {
                cout << "-- Cart is empty --" << endl;
            }

            while (!tempCart.isEmpty()) {
                FoodItem currentItem = tempCart.top();  // Use tempCart instead of user->cart
                cout << "ID: " << currentItem.id << endl;
                cout << "Name: " << currentItem.name << endl;
                cout << "Price: $" << currentItem.price << endl;
                cout << endl;
                tempCart.pop();
            }
            break;
        }
        case '4': {
            clearScreen(); // Clear the terminal screen
            if (orderQueue->isEmpty()) {
                cout << "No orders to process." << endl;
            } else {
                while (!orderQueue->isEmpty()) {
                    Order currentOrder = orderQueue->peek();
                    // Assign a random order ID
                    currentOrder.orderId = generateRandomOrderId();
                    orderHistory->addOrder(currentOrder);
                    processOrder(user, currentOrder);
                    orderQueue->dequeue();
                }
            }
            break;
        }
        case '5': {
            clearScreen(); // Clear the terminal screen
            string itemName;
            cout << "Enter the name of the food item you want to search: ";
            cin.ignore();
            getline(cin, itemName);

            int index = searchFoodItem(availableFoodItems, itemName);
            if (index != -1) {
                cout << "Food item found at index " << index << "." << endl;
            } else {
                cout << "Food item not found." << endl;
            }
            break;
        }
        case '6': {
            clearScreen(); // Clear the terminal screen
            vector<FoodItem> sortedItems = availableFoodItems;
            sort(sortedItems.begin(), sortedItems.end(), compareByPrice);
            displayAvailableFoodItems(sortedItems);
            break;
        }
        case '7': {
            clearScreen(); // Clear the terminal screen
            vector<FoodItem> sortedItems = availableFoodItems;
            sort(sortedItems.begin(), sortedItems.end(), compareByPrice);
            reverse(sortedItems.begin(), sortedItems.end());
            displayAvailableFoodItems(sortedItems);
            break;
        }
        case '8': {
            clearScreen(); // Clear the terminal screen
            displayOrderHistory(*orderHistory);
            break;
        }
        case '9': {
            clearScreen(); // Clear the terminal screen
            cout << "Exiting the program. Thank you!" << endl;
            break;
        }
        default:
            clearScreen(); // Clear the terminal screen
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void displayLogo() {
    cout << endl << endl;
    cout << " " << u8"╭━━━╮╱╱╱╱╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━╮╱╱╱╭╮" << endl;
    cout << " " << u8"┃╭━╮┃╱╱╱╱╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━╮┃╱╱╱┃┃" << endl;
    cout << " " << u8"┃┃╱┃┣━╮╭━━┫┃╭┳━┳┳━╮╭━━┳━━┳━╮╱┃┃╱┃┣╮╭┳┫┃╭┳━━┳╮╭╮" << endl;
    cout << " " << u8"┃╰━╯┃╭╮┫╭╮┃╰╯┫╭╋┫╭╮┫╭╮┃╭╮┃╭╮╮┃╰━╯┃╰╯┣┫╰╯┫╭╮┃╰╯┃" << endl;
    cout << " " << u8"┃╭━╮┃┃┃┃╰╯┃╭╮┫┃┃┃┃┃┃╰╯┃╭╮┃┃┃┃┃╭━╮┃┃┃┃┃╭╮┫╰╯┃┃┃┃" << endl;
    cout << " " << u8"╰╯╱╰┻╯╰┻━╮┣╯╰┻╯╰┻╯╰┻━╮┣╯╰┻╯╰╯╰╯╱╰┻┻┻┻┻╯╰┻━━┻┻┻╯" << endl;
    cout << " " << u8"╱╱╱╱╱╱╱╭━╯┃╱╱╱╱╱╱╱╱╭━╯┃" << std::endl;
    cout << " " << u8"╱╱╱╱╱╱╱╰━━╯╱╱╱╱╱╱╱╱╰━━╯" << std::endl;
    cout << endl << endl;
}

void printMenu() {
    cout << "=================================================" << endl;
    cout << "\tWelcome to the Food Delivery System!" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t1. Display available food items" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t2. Add food item to cart" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t3. Display cart contents" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t4. Process orders" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t5. Search for a food item by name" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t6. Sort food items by lower price" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t7. Sort food items by higher price" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t8. Display order history" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t9. Exit" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << endl << endl;
    cout << "Ｅｎｔｅｒ Ｙｏｕｒ Ｃｈｏｉｃｅ :  ";
}

void initializeVariables(User& user, vector<FoodItem>& availableFoodItems, Queue<Order>& orderQueue, OrderHistory& orderHistory) {
    // Initialize the user
    user.username = "JohnDoe";
    user.password = "password123";

    // Initialize the available food items
    FoodItem foodItem1 = {1, "Burger", 5.99};
    FoodItem foodItem2 = {2, "Pizza", 8.99};

    // Add the food items to the vector
    availableFoodItems.push_back(foodItem1);
    availableFoodItems.push_back(foodItem2);

    // Initialize the order queue and order history
    orderQueue = Queue<Order>();
    orderHistory = OrderHistory();
}


int main() {

    User user;
    vector<FoodItem> availableFoodItems;
    Queue<Order> orderQueue;
    OrderHistory orderHistory;

    initializeVariables(user, availableFoodItems, orderQueue, orderHistory);
    displayLogo();

    // Menu loop
    char choice;
    do {

        printMenu();
        cin >> choice;
        cout << endl;
        handleUserChoice(choice, &user, availableFoodItems, &orderQueue, &orderHistory);

    } while (choice != '9');

    return 0;
}

