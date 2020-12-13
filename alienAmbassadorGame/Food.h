// Food Header File
#ifndef FOOD_H
#define FOOD_H
#include <iostream>
#include <string>
using namespace std;

class Food
{
// Member functions
public:
    // Constructors
    Food();
    Food(string new_type, string new_name, double new_cost, int new_calories);

    // Setters
    void setType(string new_type);
    void setName(string new_name);
    void setCost(double new_cost);
    void setCalories(int new_calories);

    // Getters
    string getType() const;
    string getName() const;
    double getCost() const;
    int getCalories() const;

// Data members
private:
    string type;
    string name; 
    double cost;
    int calories;
};
#endif