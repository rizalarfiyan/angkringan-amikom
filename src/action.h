#ifndef ACTION_H
#define ACTION_H

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

class Action {
private:
    User user;
    vector<FoodItem> menus;
    Queue<Order> orderQueue;
    OrderHistory orderHistory;
    char choice;

public:
    Action(User user, vector<FoodItem> menus);
    void run();
    void printLogo();
    void printMenu();
    void printThankYou();
    void printInvalidChoice();
    void printInvalidFoodItemID();
    void printOrderSuccess();
    void printCartContents();
    void printEmptyCart();
    void printOrderProcessed();
    void printNoOrderProcess();
    void printInfo(Order menu);
    void printTotalPrice(double total);
    void printFoodMenuItem(FoodItem menu, int* quantity);
    void printFoodMenus(vector<FoodItem> menus);
    void printFoodMenus();
    void choiceAction();
    static string searchField(const FoodItem& item);
    static bool compareByPriceASC(const FoodItem& item1, const FoodItem& item2);
    static bool compareByPriceDESC(const FoodItem& item1, const FoodItem& item2);
    void handleChoice();
    void addToCartAction();
    FoodItem* checkValidFoodId(int selectedFoodId);
    int inputSelectedFoodId();
    int inputQuantity();
    void addToCart(FoodItem& foodItem);
    double cartContents();
    string inputSearch();
    void processOrders();
    void startQueue();
};

#include "action.cpp"

#endif
