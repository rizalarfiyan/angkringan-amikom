#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "models.h"
#include "utils.h"
#include "services/stack.h"
#include "services/queue.h"
#include "services/linkedlist.h"
#include "services/sort.h"
#include "services/search.h"

using namespace std;

// Callback function for searching in FoodItem by name
string searchField(const FoodItem& item) {
    return item.name;
}

// Comparator function for sorting food items by totalPrice in ascending order
bool compareByPriceASC(const FoodItem& item1, const FoodItem& item2) {
    return item1.price > item2.price;
}

bool compareByPriceDESC(const FoodItem& item1, const FoodItem& item2) {
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

    // Process the items in the cart
    double totalPrice = 0.0;
    cout << "Cart Contents:" << endl;
    while (!order.user.cart.isEmpty()) {
        FoodItem currentItem = order.user.cart.top();

        cout << "+-----------------------------+" << endl;
        cout << "| ID       : " << setw(17) << left << currentItem.id << " |" << endl;
        cout << "| Name     : " << setw(17) << left << currentItem.name << " |" << endl;
        cout << "| Price    : $" << setw(16) << fixed << setprecision(2) << left << currentItem.price << " |" << endl;
        cout << "| Quantity : " << setw(17) << left << order.quantity << " |" << endl;
        cout << "+-----------------------------+" << endl;

        totalPrice += (currentItem.price * order.quantity);
        order.totalPrice = totalPrice;
        cout << endl;
        order.user.cart.pop();
    }

    cout << "Total Price: $" << totalPrice << endl << endl;
    cout << "-- Order processed successfully! --" << endl;

    user->cart = Stack<FoodItem>(); // Clear the cart
}


// Display the available food items
void displayAvailableFoodItems(const vector<FoodItem>& foodItems) {
    clearScreen();
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
                clearScreen();
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
                clearScreen();
                cout << endl << "-- Invalid food item ID. Please try again. --" << endl << endl;
            }
            break;
        }
        case '3': {
            clearScreen();
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
            clearScreen();
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
            clearScreen();
            string itemName;
            cout << "Enter the name of the food item you want to search: ";
            cin.ignore();
            getline(cin, itemName);

			vector<FoodItem> results = Search<FoodItem>::fuzzy(availableFoodItems, searchField, itemName);

			for (const auto& result : results) {
				cout << "ID: " << result.id << ", Name: " << result.name << ", Price: " << result.price << endl;
			}
            break;
        }
        case '6': {
            clearScreen();
            vector<FoodItem> sortedItems = availableFoodItems;
			Sort<FoodItem>::bubble(sortedItems, compareByPriceASC);
            displayAvailableFoodItems(sortedItems);
            break;
        }
        case '7': {
            clearScreen();
            vector<FoodItem> sortedItems = availableFoodItems;
			Sort<FoodItem>::bubble(sortedItems, compareByPriceDESC);
            displayAvailableFoodItems(sortedItems);
            break;
        }
        case '8': {
            clearScreen();
            displayOrderHistory(*orderHistory);
			// orderHistory->displayOrderHistory();
            break;
        }
        case '9': {
            clearScreen();
            cout << "-- Exiting the program. Thank you! --" << endl;
            break;
        }
        default:
            clearScreen();
            cout << "-- Invalid choice. Please try again. --" << endl;
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
    cout << " " << u8"╱╱╱╱╱╱╱╭━╯┃╱╱╱╱╱╱╱╱╭━╯┃" << endl;
    cout << " " << u8"╱╱╱╱╱╱╱╰━━╯╱╱╱╱╱╱╱╱╰━━╯" << endl;
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
    cout << "\t6. Sort food items by lower" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "\t7. Sort food items by higher" << endl;
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
    FoodItem foodItem1 = {1, "Burager", 5.99};
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

