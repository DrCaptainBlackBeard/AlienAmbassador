// Alien Class Implementation 
#include "Alien.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constructors
// Default constructor
Alien::Alien()
{
    // initial condition values
    name = "";
    nourishment = 0;
    fun = 0;
    energy = 0;
    impression = 0;
}

// Parameterized constructor
Alien::Alien(string new_name, int new_nourishment, int new_fun, int new_energy, int new_impression)
{
    name = new_name;
    nourishment = new_nourishment;
    fun = new_fun;
    energy = new_energy;
    impression = new_impression;
}

// Setters
void Alien::setName(string new_name)
{
    name = new_name;
}
void Alien::setNourishment(int new_nourishment)
{
    nourishment = new_nourishment;
}
void Alien::setFun(int new_fun)
{
    fun = new_fun;
}
void Alien::setEnergy(int new_energy)
{
    energy = new_energy;
}
void Alien::setImpression(int new_impression)
{
    impression = new_impression;
}

// Function reflects Alien's pre-set conversation preferences
void Alien::talkPreferences(bool posInteraction, string subject, int modifier) // modifier adds or subtracts based on external game factors not seen in class
{
    // Positive interaction, positively effects stats
    if(posInteraction)
    {
        if(subject == "ice breaker")
        {
            impression += modifier;
        }
        else if(subject == "casual") // low risk low reward
        {
            if(getMood() > 60) // higher mood means higher range of impression
            {
                impression += randRange(3, 6);
            }
            else if(getMood() > 30)
            {
                impression += randRange(2, 3);
            }
            else
            {
                impression += 1;
            }  
        }
        else if(subject == "compliment") // more effective when in bad mood and good interaction
        {
            if(getMood() < 30) 
            {
                impression += randRange(5, 10);
            }
            else
            {
                impression += 1;
            }
        }        
        else if(subject == "joke") // more effective when in good mood
        {
            if(getMood() > 70) 
            {
                impression += randRange(4, 8);
            }
            else
            {
                impression += 1;
            }
        }
        else if(subject == "listen") // listening is how player gets insight into alien stats
        {
            impression += 3;
            // Clue player into nourishment, fun, and energy stats
            cout << "\n";
            cout << getName() << ": Overall I am feeling";
            if(getNourishment() <= 50)
            {
                cout << " hungry";
                impression -= 1;
            }
            else
            {
                cout << " satiated";
                impression += 2;
            }
            if(getFun() <= 50)
            {
                cout << ", bored";
                impression -= 1;
            }
            else
            {
                cout << ", entertained"; 
                impression += 2;
            }
            if(getEnergy() <= 40)
            {
                cout << ", and tired.";
                impression -= 1;
            }
            else
            {
                cout << ", and awake.";
                impression += 2;
            }
            // Clue player into impression
            cout << " Regardless, I want you to know that I find you";
            if(getImpression() == maxImpression) // 300 max
            {
                cout << " to be the BEST company i've had in centuries!!!" << endl;
            }
            else if(getImpression() >= 250)
            {
                cout << " quite impressive!!" << endl;  
            }
            else if(getImpression() >= 200) // indicated min. impression for win criterion (200+)
            {
                cout << " to be good company!" << endl;  
            }
            else if(getImpression() >= 100)
            {
                cout << " kind of bland." << endl;  
            }  
            else if(getImpression() >= 25)
            {
                cout << " offensive." << endl;  
            }  
            else
            {
                cout << " disguisting." << endl;
            }                           
        }
        // Headbutt at end of day for extra points
        else if(subject == "headbutt")
        {
            cout << "\n";
            cout << getName() << ": [returns the headbutt] HAHAHA! You handled that well. Have a good evening." << endl;
            impression += modifier;
        }
    }
    // Negative interaction, negatively effects stats
    else
    {
        if(subject == "ice breaker")
        {
            impression += (modifier / 2);
        }
        else if(subject == "casual") // low risk low punishment
        {
            if(getMood() <= 30) // 
            {
                impression -= randRange(3, 6);
            }
            else if(getMood() <= 60)
            {
                impression -= randRange(2, 3);
            }
            else
            {
                impression -= 1;
            }  
        }
        else if(subject == "compliment") // more punitive when in bad mood AND bad interaction
        {
            if(getMood() < 30) 
            {
                impression -= randRange(5, 10);
            }
            else
            {
                impression -= 2;
            }
        }        
        else if(subject == "joke") // more punitive when in good mood AND bad interaction
        {
            if(getMood() > 70) 
            {
                impression -= randRange(4, 8);
            }
            else
            {
                impression -= 2;
            }
        }
        else if(subject == "listen") // listening as a bad interaction only yields mood
        {
            impression -= 5;

            // Clue player into impression
            cout << "\nAll in all I've got nothing to share right now";

            if(getMood() > 75)
            {
                cout << " my friend." << endl;  
            }
            else if(getMood() > 50)
            {
                cout << " Diplomat." << endl;  
            }
            else if(getMood() > 25)
            {
                cout << " you annoying creature!" << endl;  
            }  
            else if(getMood() > 0)
            {
                cout << " you wretched cur!!" << endl;
            }
            else
            {
                cout << " YOU GIANT GLOB OF KARSEKI $@#*^@%!!!" << endl;
                // penalize overall score
            }   
        }
        else if(subject == "headbutt")
        {
            cout << "\n";
            cout << getName() << ": WATCH YOURSELF!" << endl;
            impression -= modifier;
        }
    }   
}
// Function reflects Alien's pre-set food preferences
bool Alien::foodPreferences(string foodOrder)
{
    bool likesFoodOrder = true;
    // Breakfast preferences
    if(foodOrder == "giggeon grits")
    {
        cout << name << ": Giggeon grits are my favorite - takes me back to being a soldier." << endl;
        impression += 5;
    }
    else if(foodOrder == "betol eggs & ham")
    {
        cout << name << ": Tasty! I remember crushing an enemy like a betol egg." << endl;
        impression += 2;
    }
    else if(foodOrder == "cheeri0s")
    {
        cout << name << ": These aren't even frosted!?" << endl;
        impression -= 2;
        likesFoodOrder = false;
    }
    // Lunch preferences
    else if(foodOrder == "muck zahh")
    {
        cout << name << ": I am always in the mood for 'zahhhttt' good muck! Get it?" << endl;
        impression += 5;
    }
    else if(foodOrder == "helostar snout")
    {
        cout << name << ": Kinda looks like human snout huh? Yum." << endl;
        impression += 2;
    }
    else if(foodOrder == "sorbor soup")
    {
        cout << name << ": More like 'souper' gross." << endl;
        impression -= 2;
        likesFoodOrder = false;
    }  
    // Dinner preferences
    else if(foodOrder == "skrimp sulk")
    {
        cout << name << ": So many tiny eyes! I love eating food that can see me devour it alive." << endl;
        impression += 5;
    }
    else if(foodOrder == "ulznut spagoot")
    {
        cout << name << ": Ahh yes, the authentic taste of space Italy!" << endl;
        impression += 2;
    }
    else if(foodOrder == "dejunti bowl")
    {
        cout << name << ": I'd rather 'bowl' over and die." << endl;
        impression -= 2;
        likesFoodOrder = false;
    }
    return likesFoodOrder;
}

void Alien::Eat(int calories)
{
    energy += (calories / 100);
    nourishment += (calories / 50);
}
void Alien::Rest()
{
    energy++;
    if (energy > maxEnergy)
    {
        energy = maxEnergy;
    }
}

// Getters
string Alien::getName()
{
    return name;
}
int Alien::getNourishment()
{
    if(nourishment > maxNourishment)
    {
        nourishment = maxNourishment;
    }
    else if(nourishment < 0)
    {
        nourishment = 0;
    }
    return nourishment;
}
int Alien::getFun()
{
    if(fun > maxFun)
    {
        fun = maxFun;
    }
    else if(fun < 0)
    {
        fun = 0;
    }
    return fun;
}
int Alien::getEnergy()
{
    if(energy > maxEnergy)
    {
        energy = maxEnergy;
    }
    else if(energy < 0)
    {
        energy = 0;
    }
    return energy;
}
int Alien::getImpression()
{
    if(impression > maxImpression)
    {
        impression = maxImpression;
    }
    else if(impression < 0)
    {
        impression = 0;
    }
    return impression;
}
// Mood is a percent, so range from 0 - 100
int Alien::getMood()
{  
    double moodPercent = ((double)(getEnergy() + getNourishment() + getFun() + getImpression()) / (maxEnergy + maxNourishment + maxFun + (maxImpression - 50))) * 100.0;
    // round mood to nearest whole number
    return (int)(moodPercent + 0.5);
}

/** Private member function gives a random number used for determining preferences - helps add game replayability 
// FORMULA gives us [a, b] (from Text Book)
// numIntegers = b - a + 1;
// randomNumber = (rand() % num_integers) + a;
// Formula: (rand() % b - a + 1) + a
*/
int Alien::randRange(int min, int max)
{
    // Seed random function with current time
    srand(time(NULL));
    int randNumber = ((rand() % max - min + 1) + min);
    return randNumber;
}