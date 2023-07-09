#include "utils.h"
#include <cstdlib>
#include <random>

void clearScreen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int generateRandomOrderId() {
    // Obtain a random seed from the operating system
    random_device rd;
    // Initialize the random number generator
    mt19937 gen(rd());
    // Define the range of order IDs
    uniform_int_distribution<> dis(1000, 9999);
    // Generate a random order ID
    return dis(gen);
}

string formatCurrency(double price) {
    stringstream stream;

	//* view avaliable locale in /etc/locale.gen
    stream.imbue(locale(u8"id_ID.UTF8"));
    stream << fixed << setprecision(2) << price;
    
    string formattedPrice = stream.str();
    size_t decimalPos = formattedPrice.find(".");
    if (decimalPos != string::npos) {
        formattedPrice.replace(decimalPos, 1, ".");
    }

    return "Rp " + formattedPrice;
}
