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
void processOrder(Order order) {
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
        cout << "Quantity: " << order.quantity << endl;
        totalPrice += (currentItem.price * order.quantity);
        cout << endl;
        order.user.cart.pop();
    }

    cout << "Total Price: $" << totalPrice << endl;
    cout << "Order processed successfully!" << endl;
}

// Comparator function for sorting orders by order ID in ascending order
bool compareOrdersById(const Order& order1, const Order& order2) {
    return order1.orderId < order2.orderId;
}

// Display the available food items
void displayAvailableFoodItems(const vector<FoodItem>& foodItems) {
    cout << "Available Food Items:" << endl;
    for (const auto& foodItem : foodItems) {
        cout << "ID: " << foodItem.id << endl;
        cout << "Name: " << foodItem.name << endl;
        cout << "Price: $" << foodItem.price << endl;
        cout << endl;
    }
}

// Display the order history
void displayOrderHistory(const vector<Order>& orderHistory) {
    if (orderHistory.empty()) {
        cout << "Order history is empty." << endl;
    } else {
        cout << "Order History:" << endl;
        for (const auto& order : orderHistory) {
            cout << "Order ID: " << order.orderId << endl;
            cout << "Username: " << order.user.username << endl;
            cout << "Password: " << order.user.password << endl;
            cout << "Quantity: " << order.quantity << endl;
            cout << endl;
        }
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

int main() {
    // Create a user
    User user;
    user.username = "john";
    user.password = "password";

    // Create a list of available food items
    vector<FoodItem> availableFoodItems;
    availableFoodItems.push_back({1, "Pizza", 9.99});
    availableFoodItems.push_back({2, "Burger", 5.99});
    availableFoodItems.push_back({3, "Salad", 7.99});

    // Create a queue for order processing
    queue<Order> orderQueue;

    // Create a vector to store order history
    vector<Order> orderHistory;

    // Menu loop
    char choice;
    do {
        // Display the sorting menu
        cout << "=== Selamat Datang di Angkringan Amikom ===" << endl;
        cout << "1. Display available food items" << endl;
        cout << "2. Add food item to cart" << endl;
        cout << "3. Display cart" << endl;
        cout << "4. Process orders" << endl;
        cout << "5. Search food item by name" << endl;
        cout << "6. Sort food items by low price" << endl;
        cout << "7. Sort food items by high price" << endl;
        cout << "8. Display order history" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the newline character from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case '1': {
                displayAvailableFoodItems(availableFoodItems);
                break;
            }
            case '2': {
                displayAvailableFoodItems(availableFoodItems);
                // Prompt the user to select a food item
                int selectedItemId;
                cout << "Enter the ID of the food item you want to add to the cart: ";
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
                    addToCart(&user, selectedFoodItem);

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
                    cout << "Invalid food item ID. Please try again." << endl;
                }
                break;
            }
            case '3': {
                if (user.cart.empty()) {
                    cout << "Your cart is empty." << endl;
                } else {
                    cout << "Cart Contents:" << endl;
                    stack<FoodItem> cartCopy = user.cart;
                    while (!cartCopy.empty()) {
                        FoodItem currentItem = cartCopy.top();
                        cout << "ID: " << currentItem.id << endl;
                        cout << "Name: " << currentItem.name << endl;
                        cout << "Price: $" << currentItem.price << endl;
                        cout << endl;
                        cartCopy.pop();
                    }
                }
                break;
            }
            case '4': {
                if (orderQueue.empty()) {
                    cout << "No orders to process." << endl;
                } else {
                    while (!orderQueue.empty()) {
                        Order currentOrder = orderQueue.front();
                        currentOrder.orderId = orderHistory.size() + 1; // Assign order ID
                        processOrder(currentOrder);
                        orderHistory.push_back(currentOrder);
                        orderQueue.pop();
                    }
                }
                break;
            }
            case '5': {
                string itemName;
                cout << "Enter the name of the food item you want to search: ";
                getline(cin, itemName);
                int itemIndex = searchFoodItem(availableFoodItems, itemName);
                if (itemIndex != -1) {
                    const FoodItem& foundItem = availableFoodItems[itemIndex];
                    cout << "Food item found:" << endl;
                    cout << "ID: " << foundItem.id << endl;
                    cout << "Name: " << foundItem.name << endl;
                    cout << "Price: $" << foundItem.price << endl;
                } else {
                    cout << "Food item not found." << endl;
                }
                break;
            }
            case '6': {
                sort(availableFoodItems.begin(), availableFoodItems.end(), compareByPrice);
                cout << "Food items sorted by low price." << endl;
                displayAvailableFoodItems(availableFoodItems);
                break;
            }
            case '7': {
                sort(availableFoodItems.rbegin(), availableFoodItems.rend(), compareByPrice);
                cout << "Food items sorted by high price." << endl;
                displayAvailableFoodItems(availableFoodItems);
                break;
            }
            case '8': {
                displayOrderHistory(orderHistory);
                break;
            }
            case '9': {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != '9');

    return 0;
}
