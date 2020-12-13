// Food Implementation File
#include "Food.h"
#include <iostream>
#include <string>
using namespace std;

// Constructors
Food::Food()
{
    type = "";
    name = "";
    cost = 0;
    calories = 0;
}
Food::Food(string new_type, string new_name, double new_cost, int new_calories)
{
    name = new_name;
    type = new_type;
    cost = new_cost;
    calories = new_calories;
}

// Setters
void Food::setType(string new_type)
{
    type = new_type;
}
void Food::setName(string new_name)
{
    name = new_name;
}
void Food::setCost(double new_cost)
{
    cost = new_cost;
}
void Food::setCalories(int new_calories)
{
    calories = new_calories;
}

// Getters
string Food::getType() const
{
    return type;
}
string Food::getName() const
{
    return name;
}
double Food::getCost() const
{
    return cost;
}
int Food::getCalories() const
{
    return calories;
}