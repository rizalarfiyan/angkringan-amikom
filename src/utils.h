#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <locale>
#include <iomanip>
#include <sstream>
using namespace std;

void clearScreen();
int generateRandomOrderId();
string formatCurrency(double price);

#include "utils.cpp"

#endif
