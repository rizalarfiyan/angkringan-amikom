#include <iostream>

#include "models.h"
#include "utils.h"
#include "action.h"

using namespace std;

int main() {
    clearScreen();

    User user = {
		username: "admin",
		password: "passsword"
	};

    vector<FoodItem> foodMenus{
		{1, "Nasi Goreng", 20000},
		{2, "Sate Ayam", 15000},
		{3, "Gado-gado", 18000},
		{4, "Rendang", 35000},
		{5, "Soto Ayam", 25000},
		{6, "Nasi Padang", 30000},
		{7, "Sambal Goreng Tempe", 12000},
		{8, "Bakso", 10000},
		{9, "Mie Ayam", 15000},
		{10, "Ayam Goreng", 20000},
		{11, "Teh Tarik", 8000},
		{12, "Es Teh Manis", 5000},
		{13, "Jus Jeruk", 10000},
		{14, "Es Kelapa Muda", 15000},
		{15, "Kopi Tubruk", 10000},
		{16, "Wedang Jahe", 8000},
		{17, "Es Campur", 12000},
		{18, "Es Teler", 15000},
		{19, "Bajigur", 10000},
		{20, "Es Cendol", 10000},
	};

	Action action = Action(user, foodMenus);
	action.run();

    return 0;
}

