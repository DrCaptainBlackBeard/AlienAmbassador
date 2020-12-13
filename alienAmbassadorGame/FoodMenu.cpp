// Food Menu Header File
#include "FoodMenu.h"
#include "Food.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Default constructor
FoodMenu::FoodMenu()
{
    foodCount = 0;
}
// Parametrized constructor
FoodMenu::FoodMenu(vector<Food> new_foods)
{
    foods = new_foods;
    foodCount = foods.size();
}

// The hour determines which menu is diplayed and which food items are displayed. Vector of food object details: [0]Type, [1]Name, [2]Cost, [3]Calories via overloaded constructor returns the index of chosen food item
int FoodMenu::orderFood(double gameHour, vector<Food> new_foods)
{
    string mealTime = "";
    // If hour between [0 and 2], display breakfast menu 
    if(gameHour <= 2.0)
    {
        mealTime = "breakfast";
        cout << "\n" << setfill('*') << setw(20) << "| BREAKFAST MENU |" << setfill('*') << setw(20) << '*' << "\n" << endl;
        // Output food name and cost
        for(int i = 0; i < new_foods.size(); i++)
        {
            if(new_foods[i].getType() == mealTime)
            {
                cout << "> " << new_foods[i].getName() << " $" << fixed << setprecision(2) << new_foods[i].getCost() << endl;
            }
        }
        cout << "\n" << setfill('*') << setw(40) << '*' << endl;
    }
    // If hour between (2 and 6], display lunch menu
    else if(gameHour > 2.0 && gameHour <= 6)
    {
        mealTime = "lunch";
        cout << "\n" << setfill('*') << setw(20) << "| LUNCH MENU |" << setfill('*') << setw(20) << '*' << "\n" << endl;
        // Output food name and cost
        for(int i = 0; i < new_foods.size(); i++)
        {
            if(new_foods[i].getType() == mealTime)
            {
                cout << "> " << new_foods[i].getName() << " $" << fixed << setprecision(2) << new_foods[i].getCost() << endl;
            }
        }
        cout << "\n" << setfill('*') << setw(40) << '*' << endl;
    
    }
    // If hour between (6 and 9), display dinner menu
    else if(gameHour > 6.0 && gameHour < 9.0)
    {
        mealTime = "dinner";
        cout << "\n" << setfill('*') << setw(20) << "| DINNER MENU |" << setfill('*') << setw(20) << '*' << "\n" << endl;
        // Output food name and cost
        for(int i = 0; i < new_foods.size(); i++)
        {
            if(new_foods[i].getType() == mealTime)
            {
                cout << "> " << new_foods[i].getName() << " $" << fixed << setprecision(2) << new_foods[i].getCost() << endl;
            }
        }
        cout << "\n" << setfill('*') << setw(40) << '*' << endl;
    }
    // If hour 9+ display 'CLOSED'
    else
    {
        cout << "\n" << "Screen Bot: *Bl3eP. BlUp.* C L O S E D." << endl;
        return -1;
    }

    // Prompt user for order
    string order;
    int orderIdx = 0;
    do
    {
        cout << "Write down your order ('c' to cancel ordering): ";
        getline(cin, order);
        cout << "\n";
        for(int i = 0; i < new_foods.size(); i++)
        {
            // check if player ordered right item that matches displayed menu
            if(order == new_foods[i].getName() && mealTime == new_foods[i].getType())
            {
                cout << "Screen Bot: *Bl3eP. Bl0p. Bl0op.* Your order is ready." << endl;
                orderIdx = i;
                return orderIdx;
                break;
            }
        }
        if(order != "c"){cout << "Screen Bot: *Bl3eP. Bl0op.* Please type in the right order..." << endl;}
    }while(order != "c");

    // Player cancelled order
    cout << "Screen Bot: *Bl3eP. Blo0p.* Order cancelled." << endl;
    return -2;
}

// Getters
string FoodMenu::getFoodName(int i) const
{
    return foods[i].getName();
}
string FoodMenu::getFoodType(int i) const
{
    return foods[i].getType();
}
double FoodMenu::getFoodCost(int i) const
{
    return foods[i].getCost();
}
int FoodMenu::getFoodCalories(int i) const
{
    return foods[i].getCalories();
}