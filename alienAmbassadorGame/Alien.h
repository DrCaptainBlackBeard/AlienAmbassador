// Alien Class Header
#ifndef ALIEN_H
#define ALIEN_H
#include <iostream>
#include <string>
using namespace std;

class Alien
{
public:
    // Default constructor
    Alien();

    // Parameterized constructor
    Alien(string new_name, int new_nourishment, int new_fun, int new_energy, int new_impression);

    // Setters
    void setName(string new_name);
    void setNourishment(int new_nourishment);
    void setFun(int new_fun);
    void setEnergy(int new_energy);
    void setImpression(int new_impression);

    // Function reflects Alien's pre-set conversation preferences
    void talkPreferences(bool posInteraction, string subject, int modifier = 0);
    // Function reflects Alien's pre-set food preferences
    bool foodPreferences(string foodOrder);

    void Eat(int calories);
    void Rest();

    // Getters
    string getName();
    int getNourishment();
    int getFun();
    int getEnergy();
    int getImpression();
    int getMood();

private:
    // Private Member Function (accessable only by other member functions in class)
    int randRange(int min, int max);

    // Data members
    string name;
    int nourishment;
    int fun;
    int energy;
    int impression;

    // Max amount for data members
    static const int maxNourishment = 100;
    static const int maxFun = 100;
    static const int maxEnergy = 100;
    static const int maxImpression = 300;
};
#endif
