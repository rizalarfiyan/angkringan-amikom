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
		Action(User user, vector<FoodItem> menus) {
			this->user = user;
			this->menus = menus;
			this->orderQueue = Queue<Order>();
			this->orderHistory = OrderHistory();
		};

		void run() {
			this->printLogo();
			this->choiceAction();
		};

		void printLogo() {
			cout << endl;
			cout << "  " << u8"╭━━━╮╱╱╱╱╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━╮╱╱╱╭╮" << endl;
			cout << "  " << u8"┃╭━╮┃╱╱╱╱╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━╮┃╱╱╱┃┃" << endl;
			cout << "  " << u8"┃┃╱┃┣━╮╭━━┫┃╭┳━┳┳━╮╭━━┳━━┳━╮╱┃┃╱┃┣╮╭┳┫┃╭┳━━┳╮╭╮" << endl;
			cout << "  " << u8"┃╰━╯┃╭╮┫╭╮┃╰╯┫╭╋┫╭╮┫╭╮┃╭╮┃╭╮╮┃╰━╯┃╰╯┣┫╰╯┫╭╮┃╰╯┃" << endl;
			cout << "  " << u8"┃╭━╮┃┃┃┃╰╯┃╭╮┫┃┃┃┃┃┃╰╯┃╭╮┃┃┃┃┃╭━╮┃┃┃┃┃╭╮┫╰╯┃┃┃┃" << endl;
			cout << "  " << u8"╰╯╱╰┻╯╰┻━╮┣╯╰┻╯╰┻╯╰┻━╮┣╯╰┻╯╰╯╰╯╱╰┻┻┻┻┻╯╰┻━━┻┻┻╯" << endl;
			cout << "  " << u8"╱╱╱╱╱╱╱╭━╯┃╱╱╱╱╱╱╱╱╭━╯┃" << endl;
			cout << "  " << u8"╱╱╱╱╱╱╱╰━━╯╱╱╱╱╱╱╱╱╰━━╯" << endl;
			cout << endl;
		}

		void printMenu() {
			cout << "==================================================" << endl;
			cout << "       Welcome to the Food Delivery System!       " << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   1. Display available food items" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   2. Add food item to cart" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   3. Display cart contents" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   4. Process orders" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   5. Search for a food item by name" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   6. Sort food items by lower" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   7. Sort food items by higher" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   8. Display order history" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "   9. Exit" << endl;
			cout << "--------------------------------------------------" << endl;
			cout << endl << endl;
			cout << "Ｅｎｔｅｒ Ｙｏｕｒ Ｃｈｏｉｃｅ :  ";
		}

        void printThankYou() {
            cout << "-- Exiting the program. Thank you! --" << endl;
        }

        void printInvalidChoice() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|        Invalid choice. Please try again.       |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printInvalidFoodItemID() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|     Invalid food item ID. Please try again.    |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printOrderSuccess() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|            Order successfully added!           |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printCartContents() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|                 Cart contents:                 |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printEmptyCart() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|              Opps. Cart is empty.              |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printOrderProcessed() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|         Order successfully processed!          |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

        void printNoOrderProcess() {
            cout << "+------------------------------------------------+" << endl;
            cout << "|             No orders to process.              |" << endl;
            cout << "+------------------------------------------------+" << endl;
        }

		void printInfo(Order menu) {
			cout << "+------------------------------------------------+" << endl;
			cout << "| Order ID : " << setw(36) << left << menu.orderId << "|" << endl;
			cout << "| Username : " << setw(36) << left << menu.user.username << "|" << endl;
			cout << "+------------------------------------------------+" << endl;
		}

		void printTotalPrice(double total) {
			cout << "+------------------------------------------------+" << endl;
			cout << "| Total    : $" << setw(35) << left << fixed << setprecision(2) << total << "|" << endl;
			cout << "+------------------------------------------------+" << endl;
		}

		void printFoodMenuItem(FoodItem menu, int *quantity = nullptr) {
            cout << "+------------------------------------------------+" << endl;
            cout << "| ID       : " << setw(36) << left << menu.id << "|" << endl;
            cout << "| Name     : " << setw(36) << left << menu.name << "|" << endl;
            if (quantity != nullptr) {
				cout << "| Price    : $" << setw(35) << left << fixed << setprecision(2) << (menu.price * *quantity) << "|" << endl;
				cout << "| Quantity : " << setw(36) << left << *quantity << "|" << endl;
			} else {
				cout << "| Price    : $" << setw(35) << left << fixed << setprecision(2) << menu.price << "|" << endl;
			}
            cout << "+------------------------------------------------+" << endl;
		}

		void printFoodMenus(vector<FoodItem> menus) {
			cout << "+------------------------------------------------+" << endl;
			cout << "|              Available Food Items              |" << endl;
			cout << "+------------------------------------------------+" << endl;
			for (const auto& menu : menus) {
				this->printFoodMenuItem(menu);
			}
		}

		void printFoodMenus() {
			this->printFoodMenus(this->menus);
		}

		void choiceAction() {
			do {
				this->printMenu();
				cin >> choice;
				cout << endl;
				this->handleChoice();
			} while (choice != '9');
		}

        static string searchField(const FoodItem& item) {
            return item.name;
        }

        static bool compareByPriceASC(const FoodItem& item1, const FoodItem& item2) {
            return item1.price > item2.price;
        }

        static bool compareByPriceDESC(const FoodItem& item1, const FoodItem& item2) {
            return item1.price < item2.price;
        }

		void handleChoice() {
			switch (choice) {
				case '1': {
					clearScreen();
					this->printLogo();
					this->printFoodMenus();
					break;
				}
				case '2': {
					clearScreen();
					this->printLogo();
					this->printFoodMenus();
                    this->addToCartAction();
					break;
				}
                case '3': {
                    clearScreen();
					this->printLogo();
                    this->cartContents();
                    break;
                }
                case '4': {
                    clearScreen();
                    this->processOrders();
                    break;
                }
                case '5': {
                    clearScreen();
                    string itemName = this->inputSearch();
                    vector<FoodItem> results = Search<FoodItem>::fuzzy(menus, searchField, itemName);
                    this->printFoodMenus(results);
                    break;
                }
                case '6': {
                    clearScreen();
                    vector<FoodItem> sortedItems = menus;
                    Sort<FoodItem>::bubble(menus, compareByPriceASC);
                    this->printFoodMenus(sortedItems);
                    break;
                }
                case '7': {
                    clearScreen();
                    vector<FoodItem> sortedItems = menus;
                    Sort<FoodItem>::bubble(sortedItems, compareByPriceDESC);
                    this->printFoodMenus(sortedItems);
                    break;
                }
                case '8': {
                    clearScreen();
                    orderHistory.displayOrderHistory();
                    break;
                }
                case '9': {
                    clearScreen();
                    this->printThankYou();
                    break;
                }
                default:
                    clearScreen();
                    this->printInvalidChoice();
                    break;
            }
		}

        void addToCartAction() {
            int selectedFoodId = this->inputSelectedFoodId();
            FoodItem* selectedFoodItem = this->checkValidFoodId(selectedFoodId);
            if (selectedFoodItem != nullptr) {
                this->addToCart(*selectedFoodItem);
                int quantity = this->inputQuantity();
                this->createOrderHistory(quantity);
                clearScreen();
				this->printLogo();
                this->printOrderSuccess();
            } else {
                clearScreen();
				this->printLogo();
                this->printInvalidFoodItemID();
            }
        }

        FoodItem* checkValidFoodId(int selectedFoodId) {
            FoodItem* selectedFoodItem = nullptr;
            for (auto& foodItem : menus) {
                if (foodItem.id == selectedFoodId) {
                    selectedFoodItem = &foodItem;
                    break;
                }
            }
            return selectedFoodItem;
        }

        int inputSelectedFoodId() {
            int selectedFoodId;
			cout << "+------------------------------------------------+" << endl;
            cout << "| ENTER THE FOOD ID TO ADD THE CART              |" << endl;
			cout << "+------------------------------------------------+" << endl;
            cout << "Food ID: ";
            cin >> selectedFoodId;
            return selectedFoodId;
        }

        int inputQuantity() {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            return quantity;
        }

        void createOrderHistory(int quantity) {
            Order order;
             // Temporary order ID, will be assigned later
            order.orderId = -1;
            order.user = this->user;
            order.quantity = quantity;
            this->orderQueue.enqueue(order);
        }

		void addToCart(FoodItem& foodItem) {
			FoodItem newItem = foodItem;
			user.cart.push(newItem);
		}

		void cartContents() {
			Stack<FoodItem> tempCart = user.cart;

			if (tempCart.isEmpty()) {
                this->printEmptyCart();
                return;
			}

			this->printCartContents();
			while (!tempCart.isEmpty()) {
				FoodItem currentItem = tempCart.top();
                //! fixme later
                this->printFoodMenuItem(currentItem);
				tempCart.pop();
			}
		}

		string inputSearch() {
			string itemName;
			cout << "Enter the name of the food item you want to search: ";
			cin.ignore();
			getline(cin, itemName);
			return itemName;
		}

		void processOrders() {
			if (this->orderQueue.isEmpty()) {
				this->printLogo();
				this->printNoOrderProcess();
			} else {
				while (!this->orderQueue.isEmpty()) {
					Order currentOrder = this->orderQueue.peek();
					currentOrder.orderId = generateRandomOrderId();
					orderHistory.addOrder(currentOrder);
					bool isLast = this->orderQueue.isLast();
					this->processOrder(currentOrder, isLast);
					this->orderQueue.dequeue();
				}

			}
		}

		void processOrder(Order order, bool isLast) {
			if (isLast) {
				this->printInfo(order);
				this->printCartContents();
			}

			// Process the items in the cart
			double totalPrice = 0.0;
			while (!order.user.cart.isEmpty()) {
				FoodItem currentItem = order.user.cart.top();
				if (isLast) {
					this->printFoodMenuItem(currentItem, &order.quantity);
				}
				totalPrice += (currentItem.price * order.quantity);
				order.totalPrice = totalPrice;
				order.user.cart.pop();
			}

			if (isLast) {
				this->printTotalPrice(totalPrice);
				this->printOrderProcessed();
			}

			user.cart = Stack<FoodItem>();
		}
};

int main() {
    clearScreen();

    User user = {
		"admin",
		"passsword"
	};

    vector<FoodItem> availableFoodItems{
		{1, "Burger", 5.99},
		{2, "Pizza", 8.99},
		{3, "Es Teh", 8.99},
		{4, "Es Jeruk", 8.99},
		{5, "Kerupuk", 8.99},
		{6, "Nasi", 8.99},
		{7, "Sayur", 8.99},
		{8, "Sambal", 8.99},
	};

	Action action = Action(user, availableFoodItems);
	action.run();

    return 0;
}

