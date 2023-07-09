#include "action.h"

Action::Action(User user, vector<FoodItem> menus) {
	this->user = user;
	this->menus = menus;
	this->orderQueue = Queue<Order>();
	this->orderHistory = OrderHistory();
};

void Action::run() {
	this->printLogo();
	this->choiceAction();
};

void Action::printLogo() {
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

void Action::printMenu() {
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

void Action::printThankYou() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|        Exiting the program. Thank you!         |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printInvalidChoice() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|        Invalid choice. Please try again.       |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printInvalidFoodItemID() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|     Invalid food item ID. Please try again.    |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printOrderSuccess() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|            Order successfully added!           |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printCartContents() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|                 Cart contents:                 |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printEmptyCart() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|              Opps. Cart is empty.              |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printOrderProcessed() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|         Order successfully processed!          |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printNoOrderProcess() {
	cout << "+------------------------------------------------+" << endl;
	cout << "|             No orders to process.              |" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printInfo(Order menu) {
	cout << "+------------------------------------------------+" << endl;
	cout << "| Order ID : " << setw(36) << left << menu.orderId << "|" << endl;
	cout << "| Username : " << setw(36) << left << menu.user.username << "|" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printTotalPrice(double total) {
	cout << "+------------------------------------------------+" << endl;
	cout << "| Total    : " << setw(36) << left << formatCurrency(total) << "|" << endl;
	cout << "+------------------------------------------------+" << endl;
}

void Action::printFoodMenuItem(FoodItem menu, int *quantity = nullptr) {
	cout << "+------------------------------------------------+" << endl;
	cout << "| ID       : " << setw(36) << left << menu.id << "|" << endl;
	cout << "| Name     : " << setw(36) << left << menu.name << "|" << endl;
	if (quantity != nullptr) {
		string quantityStr = to_string(*quantity) + " x (" + formatCurrency(menu.price) + ")"; 
		cout << "| Price    : " << setw(36) << left << formatCurrency(menu.price * *quantity) << "|" << endl;
		cout << "| Quantity : " << setw(36) << left << quantityStr << "|" << endl;
	} else {
		cout << "| Price    : " << setw(36) << left << formatCurrency(menu.price) << "|" << endl;
	}
	cout << "+------------------------------------------------+" << endl;
}

void Action::printFoodMenus(vector<FoodItem> menus) {
	cout << "+------------------------------------------------+" << endl;
	cout << "|              Available Food Items              |" << endl;
	cout << "+------------------------------------------------+" << endl;
	for (const auto& menu : menus) {
		this->printFoodMenuItem(menu);
	}
}

void Action::printFoodMenus() {
	this->printFoodMenus(this->menus);
}

void Action::choiceAction() {
	do {
		this->printMenu();
		cin >> choice;
		cout << endl;
		this->handleChoice();
	} while (choice != '9');
}

string Action::searchField(const FoodItem& item) {
	return item.name;
}

bool Action::compareByPriceASC(const FoodItem& item1, const FoodItem& item2) {
	return item1.price > item2.price;
}

bool Action::compareByPriceDESC(const FoodItem& item1, const FoodItem& item2) {
	return item1.price < item2.price;
}

void Action::handleChoice() {
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
			this->printLogo();
			this->processOrders();
			break;
		}
		case '5': {
			clearScreen();
			this->printLogo();
			string itemName = this->inputSearch();
			vector<FoodItem> results = Search<FoodItem>::fuzzy(menus, searchField, itemName);
			this->printFoodMenus(results);
			break;
		}
		case '6': {
			clearScreen();
			this->printLogo();
			vector<FoodItem> sortedItems = menus;
			Sort<FoodItem>::bubble(menus, compareByPriceASC);
			this->printFoodMenus(sortedItems);
			break;
		}
		case '7': {
			clearScreen();
			this->printLogo();
			vector<FoodItem> sortedItems = menus;
			Sort<FoodItem>::bubble(sortedItems, compareByPriceDESC);
			this->printFoodMenus(sortedItems);
			break;
		}
		case '8': {
			clearScreen();
			this->printLogo();
			orderHistory.displayOrderHistory();
			break;
		}
		case '9': {
			clearScreen();
			this->printLogo();
			this->printThankYou();
			break;
		}
		default:
			clearScreen();
			this->printLogo();
			this->printInvalidChoice();
			this->printMenu();
			break;
	}
}

void Action::addToCartAction() {
	int selectedFoodId = this->inputSelectedFoodId();
	FoodItem* selectedFoodItem = this->checkValidFoodId(selectedFoodId);
	if (selectedFoodItem != nullptr) {
		int quantity = this->inputQuantity();
		selectedFoodItem->quantity = quantity;
		this->addToCart(*selectedFoodItem);
		clearScreen();
		this->printLogo();
		this->printOrderSuccess();
	} else {
		clearScreen();
		this->printLogo();
		this->printInvalidFoodItemID();
	}
}

FoodItem* Action::checkValidFoodId(int selectedFoodId) {
	FoodItem* selectedFoodItem = nullptr;
	for (auto& foodItem : menus) {
		if (foodItem.id == selectedFoodId) {
			selectedFoodItem = &foodItem;
			break;
		}
	}
	return selectedFoodItem;
}

int Action::inputSelectedFoodId() {
	int selectedFoodId;
	cout << "+------------------------------------------------+" << endl;
	cout << "| ENTER THE FOOD ID TO ADD THE CART              |" << endl;
	cout << "+------------------------------------------------+" << endl;
	cout << "Food ID: ";
	cin >> selectedFoodId;
	return selectedFoodId;
}

int Action::inputQuantity() {
	int quantity;
	cout << "Enter the quantity: ";
	cin >> quantity;
	return quantity;
}

void Action::addToCart(FoodItem& foodItem) {
	FoodItem newItem = foodItem;
	user.cart.push(newItem);
}

double Action::cartContents() {
	Stack<FoodItem> tempCart = user.cart;
	double totalPrice = 0.0;

	if (tempCart.isEmpty()) {
		this->printEmptyCart();
		return totalPrice;
	}

	this->printCartContents();
	while (!tempCart.isEmpty()) {
		FoodItem currentItem = tempCart.top();
		totalPrice += (currentItem.price * currentItem.quantity);
		this->printFoodMenuItem(currentItem, &currentItem.quantity);
		tempCart.pop();
	}
	this->printTotalPrice(totalPrice);
	return totalPrice;
}

string Action::inputSearch() {
	string itemName;
	cout << "Enter the name of the food item you want to search: ";
	cin.ignore();
	getline(cin, itemName);
	return itemName;
}

void Action::processOrders() {
	Order order;
	order.orderId = generateRandomOrderId();
	order.user = this->user;
	order.items = this->user.cart;

	this->printInfo(order);
	double totalPrice = this->cartContents();		
	order.totalPrice = totalPrice;
	this->orderQueue.enqueue(order);

	this->startQueue();
	user.cart = Stack<FoodItem>();
}

void Action::startQueue() {
	if (this->orderQueue.isEmpty()) {
		this->printLogo();
		this->printNoOrderProcess();
	} else {
		while (!this->orderQueue.isEmpty()) {
			Order currentOrder = this->orderQueue.peek();
			this->orderHistory.addOrder(currentOrder);
			this->orderQueue.dequeue();
		}
		this->printOrderProcessed();
	}
}