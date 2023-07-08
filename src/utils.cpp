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
