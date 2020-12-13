// Game Stats Header
#ifndef GAMESTATS_H
#define GAMESTATS_H
#include "Alien.h"
#include <iostream>
#include <string>
using namespace std;

class GameStats
{
// Member functions
public:
    // Default Constructor
    GameStats();

    // Setters 
    void setPlayerName(string new_playerName); 
    void setDifficulty(Alien &alienStats, int difficulty);
    void interactionCount(bool positiveInteraction);
    bool spendMoney(double amtSpent);
    void addMoney(double amtAdd);
    void setGameOver(bool new_gameOver);
    void setWin(bool new_win = false);

    // Getters 
    string getPlayerName();
    string getDifficulty();
    int getPositiveInteractions();
    int getNegativeInteractions();
    int getTotalInteractions();
    double getMoney();
    bool getGameOver();
    bool getWin();
    double getHours();
    double getTotalHours();
    int getDays();
    int getMaxDays();
    int getDailyScore();
    int getScore();

    void displayStats();
    void passTime(Alien &alienStats, double hours = 0.5, bool rest = false);
  
private:
    // Private member function (to be used internally)
    void delay(); 

    // Data members  
    Alien alien;
    string playerName;
    string difficulty;
    int posInteractions;
    int negInteractions;
    double money;
    bool gameOver;
    double hours;
    double totalHours;
    static const int hoursPerDay = 10; // set to 10 for default game design.
    int days;
    int maxDays;
    int dailyScore;
    int score;
    bool win;
};
#endif
