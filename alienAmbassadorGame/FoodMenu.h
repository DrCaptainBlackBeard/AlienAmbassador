// Food Menu Header File
#ifndef FOODMENU_H
#define FOODMENU_H
#include "Food.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FoodMenu
{
public:
    // Constructors
    // Default constructor
    FoodMenu();
    // Parametrized constructor
    FoodMenu(vector<Food> new_foods);

    // The hour determines which menu is diplayed and which food items are displayed, return index of chosen item
    int orderFood(double gameHour, vector<Food> new_foods);

    // Getters
    string getFoodName(int i) const;
    string getFoodType(int i) const;
    double getFoodCost(int i) const;
    int getFoodCalories(int i) const;
    
// Data members
private:
    int foodCount;
    vector<Food> foods;
};
#endif