#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

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
    stack<FoodItem> cart;
};

// Struct to represent an order
struct Order {
    int orderId, quantity;
    User user;
};

// Struct for a node in the order history linked list
struct Node {
    Order order;
    Node* next;
};

// Struct to represent the order history linked list
// Struct to represent the order history linked list
struct OrderHistoryLinkedList {
    Node* head;
    int size; // New member variable to keep track of the size

    OrderHistoryLinkedList() : head(nullptr), size(0) {}

    ~OrderHistoryLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertOrder(const Order& order) {
        Node* newNode = new Node;
        newNode->order = order;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        size++; // Increase the size after inserting an order
    }

    void displayOrderHistory() {
        Node* temp = head;
        if (temp == nullptr) {
            cout << "No order history." << endl;
            return;
        }

        cout << "Order History:" << endl;
        while (temp != nullptr) {
            cout << "Order ID: " << temp->order.orderId << endl;
            cout << "Username: " << temp->order.user.username << endl;

            // Display the items in the order
            cout << "Cart Contents:" << endl;
            while (!temp->order.user.cart.empty()) {
                FoodItem currentItem = temp->order.user.cart.top();
                cout << "ID: " << currentItem.id << endl;
                cout << "Name: " << currentItem.name << endl;
                cout << "Price: $" << currentItem.price << endl;
                cout << "Quantity: " << temp->order.quantity << endl;
                cout << endl;
                temp->order.user.cart.pop();
            }

            temp = temp->next;
        }
    }
};



// Comparator function for sorting food items by name in alphabetical order
bool compareByName(const FoodItem& item1, const FoodItem& item2) {
    return item1.name < item2.name;
}

// Comparator function for sorting food items by price in ascending order
bool compareByPrice(const FoodItem& item1, const FoodItem& item2) {
    return item1.price < item2.price;
}

// Function to add a food item to the cart
void addToCart(User* user, FoodItem* foodItem) {
    user->cart.push(*foodItem);
    cout << "Food item added to the cart!" << endl;
}

// Function to process an order
void processOrder(Order order, OrderHistoryLinkedList& orderHistory) {
    cout << "Processing Order ID: " << order.orderId << endl;
    cout << "Username: " << order.user.username << endl;
    cout << "Password: " << order.user.password << endl;

    // Process the items in the cart
    double totalPrice = 0.0;
    cout << "Cart Contents:" << endl;
    while (!order.user.cart.empty()) {
        FoodItem currentItem = order.user.cart.top();
        cout << "ID: " << currentItem.id << endl;
        cout << "Name: " << currentItem.name << endl;
        cout << "Price: $" << currentItem.price << endl;
        totalPrice += currentItem.price;
        order.user.cart.pop();
    }
    cout << "Total Price: $" << totalPrice << endl;
    cout << "Order processed successfully!" << endl;

    // Assign the order ID
    order.orderId = orderHistory.size + 1;

    // Insert the order into the order history
    orderHistory.insertOrder(order);
}


// Function to display the available food items
void displayAvailableFoodItems(const vector<FoodItem>& foodItems) {
    cout << "Available Food Items:" << endl;
    for (const auto& item : foodItems) {
        cout << "ID: " << item.id << endl;
        cout << "Name: " << item.name << endl;
        cout << "Price: $" << item.price << endl;
        cout << endl;
    }
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

// Function to register a new user
void registerUser(vector<User>& users, OrderHistoryLinkedList& orderHistory) {
    User newUser;
    cout << "=== User Registration ===" << endl;
    cout << "Enter a username: ";
    cin >> newUser.username;

    // Check if the username already exists
    for (const auto& user : users) {
        if (user.username == newUser.username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> newUser.password;

    string passwordConfirmation;
    cout << "Confirm your password: ";
    cin >> passwordConfirmation;

    if (newUser.password != passwordConfirmation) {
        cout << "Password confirmation does not match. Please try again." << endl;
        return;
    }

    users.push_back(newUser);
    cout << "Registration successful!" << endl;
}

int main() {
    // Create a vector to store registered users
    vector<User> registeredUsers;

    // Create a list of available food items
    vector<FoodItem> availableFoodItems;
    availableFoodItems.push_back({1, "Pizza", 9.99});
    availableFoodItems.push_back({2, "Burger", 5.99});
    availableFoodItems.push_back({3, "Salad", 7.99});

    // Create a queue for order processing
    queue<Order> orderQueue;

    // Create an instance of OrderHistoryLinkedList
    OrderHistoryLinkedList orderHistory;

    // Menu loop
    char choice;
    do {
        // Display the main menu
        cout << "=== Selamat Datang di Angkringan Amikom ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the newline character from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case '1': {
                registerUser(registeredUsers, orderHistory);
                break;
            }
            case '2': {
                string username, password;
                cout << "=== User Login ===" << endl;
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;

                // Find the user by username
                bool userFound = false;
                for (const auto& user : registeredUsers) {
                    if (user.username == username && user.password == password) {
                        userFound = true;
                        User loggedInUser = user;

                        // User menu loop
                        char userChoice;
                        do {
                            cout << "=== User Menu ===" << endl;
                            cout << "1. Display available food items" << endl;
                            cout << "2. Add item to cart" << endl;
                            cout << "3. View cart" << endl;
                            cout << "4. Checkout" << endl;
                            cout << "5. Search for a food item" << endl;
                            cout << "6. Sort food items by name" << endl;
                            cout << "7. Sort food items by price (low to high)" << endl;
                            cout << "8. Display order history" << endl;
                            cout << "9. Logout" << endl;
                            cout << "Enter your choice: ";
                            cin >> userChoice;

                            // Clear the newline character from the input buffer
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            switch (userChoice) {
                                case '1': {
                                    displayAvailableFoodItems(availableFoodItems);
                                    break;
                                }
                                case '2': {
                                    int itemId;
                                    cout << "Enter the ID of the food item: ";
                                    cin >> itemId;
                                    // Find the food item by ID
                                    auto it = find_if(availableFoodItems.begin(), availableFoodItems.end(),
                                                      [itemId](const FoodItem& item) { return item.id == itemId; });
                                    if (it != availableFoodItems.end()) {
                                        addToCart(&loggedInUser, &(*it));
                                        // Prompt the user for the quantity
                                        int quantity;
                                        cout << "Enter the quantity: ";
                                        cin >> quantity;

                                        // Create an order and enqueue it for processing
                                        Order order;
                                        order.orderId = -1; // Temporary order ID, will be assigned later
                                        order.user = user;
                                        order.quantity = quantity;
                                        orderQueue.push(order);

                                        cout << "Order placed successfully!" << endl;
                                    } else {
                                        cout << "Invalid item ID." << endl;
                                    }
                                    break;
                                }
                                case '3': {
                                    cout << "Cart Contents:" << endl;
                                    stack<FoodItem> tempCart = loggedInUser.cart;
                                    while (!tempCart.empty()) {
                                        FoodItem currentItem = tempCart.top();
                                        cout << "ID: " << currentItem.id << endl;
                                        cout << "Name: " << currentItem.name << endl;
                                        cout << "Price: $" << currentItem.price << endl;
                                        cout << endl;
                                        tempCart.pop();
                                    }
                                    break;
                                }
                                case '4': {
                                    // Process the order
                                    if (!orderQueue.empty()) {
                                        Order nextOrder = orderQueue.front();
                                        orderQueue.pop();
                                        processOrder(nextOrder, orderHistory);
                                    } else {
                                        cout << "No orders in the queue." << endl;
                                    }
                                    break;
                                }

                                case '5': {
                                    string itemName;
                                    cout << "Enter the name of the food item: ";
                                    cin >> itemName;
                                    int itemIndex = searchFoodItem(availableFoodItems, itemName);
                                    if (itemIndex != -1) {
                                        cout << "Item found at index: " << itemIndex << endl;
                                    } else {
                                        cout << "Item not found." << endl;
                                    }
                                    break;
                                }
                                case '6': {
                                    sort(availableFoodItems.begin(), availableFoodItems.end(), compareByName);
                                    cout << "Food items sorted by name." << endl;
                                    break;
                                }
                                case '7': {
                                    sort(availableFoodItems.begin(), availableFoodItems.end(), compareByPrice);
                                    cout << "Food items sorted by price (low to high)." << endl;
                                    break;
                                }
                                case '8': {
                                    orderHistory.displayOrderHistory();
                                    break;
                                }
                                case '9': {
                                    cout << "Logging out..." << endl;
                                    break;
                                }
                                default: {
                                    cout << "Invalid choice. Please try again." << endl;
                                    break;
                                }
                            }
                        } while (userChoice != '9');
                        break;
                    }
                }

                if (!userFound) {
                    cout << "Invalid username or password." << endl;
                }
                break;
            }
            case '3': {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != '3');

    return 0;
}
