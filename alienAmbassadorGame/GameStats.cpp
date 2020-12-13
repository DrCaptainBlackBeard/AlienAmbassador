// Game Stats Implementation
// Keep track of important game stats and player stats
#include "Alien.h"
#include "GameStats.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Default Constructor
GameStats::GameStats()
{
    playerName = "";
    difficulty = "";
    money = 0;
    posInteractions = 0;
    negInteractions = 0;
    hours = 0;
    totalHours = 0;
    days = 1; // start day 1
    maxDays = 0;
    dailyScore = 0;
    score = 0;
    gameOver = false;
    win = false;
}

// Setters 
void GameStats::setPlayerName(string new_playerName)
{
    playerName = new_playerName;
}
// Function sets game difficulty from easy, normal or difficult. Difficulty effects game stat happenings
void GameStats::setDifficulty(Alien &alienStats, int chosen_difficulty)
{
    // Easy
    if(chosen_difficulty == 1)
    {
        difficulty = "Easy";
        cout << "You've chosen 'Easy'." << endl;
        alienStats.setName("Gorlock the Beneficent");
        alienStats.setNourishment(90);
        alienStats.setFun(90);
        alienStats.setEnergy(100);
        alienStats.setImpression(125);
        money = 150;
        hours = 0;
        totalHours = 0;  
        maxDays = 10; // should be 10 by original design
    }
    // Normal
    else if(chosen_difficulty == 2)
    {
        difficulty = "Normal";
        cout << "You've chosen 'Normal'." << endl;
        alienStats.setName("Gorlock the Bold");
        alienStats.setNourishment(80);
        alienStats.setFun(80);
        alienStats.setEnergy(90);
        alienStats.setImpression(100);
        money = 100;
        hours = 0;
        totalHours = 0;  
        maxDays = 7; // should be 7 by original design
    }
    // Difficult
    else if(chosen_difficulty == 3)
    {
        difficulty = "Difficult";
        cout << "You've chosen 'Difficult'. Good luck!" << endl;
        alienStats.setName("Gorlock the Destroyer");
        alienStats.setNourishment(70);
        alienStats.setFun(50);
        alienStats.setEnergy(70);
        alienStats.setImpression(50);
        money = 50;
        hours = 0;
        totalHours = 0;  
        maxDays = 5; // should be 5 by original design
    }
}
int GameStats::getPositiveInteractions()
{
    return posInteractions;
}
int GameStats::getNegativeInteractions()
{
    return negInteractions;
}
// Function counts the number of interactions (pos or neg) per game
void GameStats::interactionCount(bool positiveInteraction)
{ 
    if(positiveInteraction)
    {
        posInteractions++;
    }
    else
    {
        negInteractions++;
    }   
}
// Function spends player's money. Returns false if there is not enough money.
bool GameStats::spendMoney(double amtSpent)
{
    bool enoughMoney = true;
    // Check if enough money
    if((money - amtSpent) >= 0.0)
    {
        money -= amtSpent;
    }
    else
    {
        cout << "** insufficient funds **" << endl;
        enoughMoney = false;
    }
    return enoughMoney;
}
// Function adds player money.
void GameStats::addMoney(double amtAdd)
{
    money += amtAdd;
}
// Used to determine if game is over to stop the main game loop
void GameStats::setGameOver(bool new_gameOver)
{
    gameOver = new_gameOver;
}
// Used to determine if player WON or LOST game.
void GameStats::setWin(bool new_win)
{
    win = new_win;
}


// Getters 
string GameStats::getPlayerName()
{
    return playerName;
}
string GameStats::getDifficulty()
{
    return difficulty;
}
double GameStats::getMoney()
{
    return money;
}
int GameStats::getTotalInteractions()
{
    return posInteractions + negInteractions;
}
double GameStats::getHours()
{
    return hours;
}
double GameStats::getTotalHours()
{
    return totalHours;
}
int GameStats::getDays()
{
    return days;
}
int GameStats::getMaxDays()
{
    return maxDays;
}
// Calculates score so far in the day
int GameStats::getDailyScore()
{
    // Calculate score
    dailyScore = ((20 * posInteractions) + (2 * money) + alien.getImpression()) - ((5 * negInteractions) - (10 * days) - (totalHours + 0.5));
    // Make sure daily score is positive
    if(dailyScore < 0 || getTotalInteractions() == 0)
    {
        dailyScore = 0;
    }
    return dailyScore;
}

// Retrieves player current score
int GameStats::getScore()
{
    // Make sure score is positive
    if(score < 0)
    {
        score = 0;
    }

    // Score bonus if game won
    if(win)
    {
        // Reward winning player with points based off difficulty
        if(difficulty == "Difficult")
        {
            score += 600;
            cout << " [ BONUS 600pts for Winning on 'Difficult' ]" << endl;
        }
        else if(difficulty == "Normal")
        {
            score += 400;
            cout << " [ BONUS 400pts for Winning on 'Normal' ]" << endl;
        }
        else // Player chose "Easy"
        {
            score += 200;
            cout << " [ BONUS 200pts for Winning on 'Easy' ]" << endl;
        }
    }
    return score;
}
bool GameStats::getGameOver()
{
    return gameOver;
}
bool GameStats::getWin()
{
    return win;
}
void GameStats::displayStats()
{
    cout << "\n" << setfill('#') << setw(40) << "| LOG |" << setw(40) << '#' << endl;
    cout << "\n";
    // Days and Hour
    cout << "   Day " << days << "/" << maxDays;
    cout << " | Hour: " << fixed << setprecision(2) << hours << "/" << hoursPerDay << endl;
    cout << "\n";
    // Money
    cout << "   > $" << fixed << setprecision(2) << money << endl;
    // Interactions
    cout << "   > " << getTotalInteractions() << " Interactions:" << endl;
    cout << "         Positive(+) " << posInteractions << endl;
    cout << "         Negative(-) " << negInteractions << endl;
    // Current Score
    cout << "   > Daily Score: " << getDailyScore() << endl;
    cout << "   > Total Score (updates next day): "  << getScore() << endl;
    cout << "\n";
    cout << setfill('#') << setw(80) << '#' << endl;
}

// Simulates in game Time - default time per interaction is 0.5 Sumacian Hours, but depending on the activity the time varies.
void GameStats::passTime(Alien &alienStats, double new_hours, bool rest)
{
    // As time goes by, Alien gets hungrier, more bored, and loses energy.
    alienStats.setNourishment(alienStats.getNourishment() - ((new_hours + 0.50) * 2));
    alienStats.setFun(alienStats.getFun() - ((new_hours + 0.50) * 2));
    alienStats.setEnergy(alienStats.getEnergy() - ((new_hours + 0.50) * 2));
    totalHours += new_hours; // Total game hours 
    hours += new_hours; // Hours for the day

    if(alienStats.getEnergy() <= 15)
    {
        cout << "\n";
        cout << "[ Gorlock yawns deeply. He seems to be nodding off... ]" << endl;
        delay();
    }

    // Check if time to move on to next day then reset time and day
    // This means player didn't rest before 10 hours. Also energy = 0 means Gorlock is tired
    if((hours > hoursPerDay && !rest) || alienStats.getEnergy() == 0)
    {
        // Calculate how many hours user went over
        double overHours = (hours - hoursPerDay);
        
        // If user went over 10 hours per day - roll hours over
        if(overHours > 0)
        {
            totalHours -= overHours;
            // Roll hours over to next day
            hours = overHours;
        }
        else
        {
            hours = 0;
        }

        // Did not rest before new day - player is penalized by affecting alien interaction and impression
        alienStats.setImpression(alienStats.getImpression() - (overHours + 0.50));
        negInteractions++;
        
        // Gorlock's response to not resting before the hour was too late
        if(alienStats.getEnergy() == 0)
        {
            cout << "     [  Gorlock yawns and can barely keep his eyes open. ]"<< endl;
            delay();
            cout << alienStats.getName() << ": I don't have the energy to go on..." << endl;
            delay();
            cout << "     [  Before you have time to respond, Gorlock passes out on the spot. You don't dare offend him further and do the same. ]"<< endl;
            delay();
        }
        // Went over hours
        else
        {
            cout << "\n";
            cout << "     [  Gorlock angrily stops you from doing anything else. ]"<< endl;
            delay();
            cout << alienStats.getName() << ": You kept me up " << overHours << " hours longer than usual!" << endl;
            delay();
            cout << "     [  Before you have time to respond, Gorlock passes out on the spot. You don't dare offend him and do the same. ]"<< endl;
            delay();
        }

        // Move on to next day - 70/100 energy because slept on ground
        alienStats.setEnergy(70);
        days++;

        // Check if completed last day without peace offer
        if(days == maxDays + 1) // day 7/7 should still be played out
        {
            cout << "\n";
            cout << "     [  You wake up on the floor and see that it's Day " << days << " and your time is up. ]"<< endl;
            delay();
            cout << "     [  Gorlock approaches you with a dark look in his eyes. ]"<< endl;
            delay();
            cout << alienStats.getName() << ": GET OFF MY FLOOR! You've overstayed your welcome Ambassador. Diplomacy is dead." << endl;
            delay();
            cout << alienStats.getName() << ": Someone will escort you to your ship, but I reccomend you leave quickly...we're firing the sumacian M.E.G.G.U.H. Cannon..." << endl;

            // End game - lose scenario
            setWin(false);
            gameOver = true;
        }
        // Check if last day
        else if(days == maxDays)
        {
            cout << "\n";
            cout << "     [  You wake up on the floor and see that it's Day " << days << " Hour " << hours << "/10.0 ]." << " This is the final day, make it count! ]" << endl;
        }
        // Another day
        else
        {
            cout << "\n";
            cout << "     [  You wake up on the floor and see that it's Day " << days << " Hour " << hours << "/10.0 ]" << endl;
        }
        delay();
    }
    // Player rested before the 10th hour WITHOUT PEACE OFFER
    else if(rest)
    {        
        // Move on to next day - 100/100 energy because rested (presumably on bed)
        posInteractions++;
        alienStats.setEnergy(100);
        days++;
        
        // reset hour
        hours = 0;

        // Check if completed last day
        if(days == maxDays + 1) 
        {
            cout << "\n";
            cout << "     [  You wake up and see that it's Day " << days << " and your time is up. ]"<< endl;
            delay();
            cout << "     [  Gorlock approaches you with a dark look in his eyes. ]"<< endl;
            delay();
            cout << alienStats.getName() << ": Hope you're well rested! You've overstayed your welcome Ambassador. Diplomacy is dead." << endl;
            delay();
            cout << alienStats.getName() << ": Someone will escort you to your ship, but I reccomend you leave quickly...we're firing the sumacian M.E.G.G.U.H. Cannon..." << endl;

            // End game - lose scenario
            setWin(false);
            gameOver = true;
            // End game
            gameOver = true;
        }
        // Did not complete last day yet
        else
        {
            // Update Daily Stats
            
            // Update money $
            double dailyDeposit = 0;
            // UNE sends you some funds each day (amount depends on difficulty)
            if(difficulty == "easy")
            {
                dailyDeposit = 60;
            }
            else if(difficulty == "normal")
            {
                dailyDeposit = 50;
            }
            else // difficult
            {
                dailyDeposit = 30;
            }
            money += dailyDeposit;
            
            // Update total score
            int previousDayScore = dailyScore;
            score += dailyScore;

            // Reset daily score
            dailyScore = 0;

            // Check if last day
            if(days == maxDays)
            {
                cout << "\n";
                cout << "     [  You wake up and see that it's Day " << days << " Hour " << fixed << setprecision(1) << hours << "/10.0 ]" << ". This is the final day, make it count!]" << endl;
                cout << "     [  The UNE has deposited $" << fixed << setprecision(2) << dailyDeposit <<  " into your account. ]" << endl;
                cout << "     [  Previous days score of " << previousDayScore << "pts added to total score. New total score: " << score << "pts. ]" << endl;
            }
            // Another day
            else
            {
                cout << "\n";
                cout << "     [  You wake up and see that it's Day " << days << " Hour " << fixed << setprecision(1) << hours << "/10.0 ]" << endl;
                cout << "     [  The UNE has deposited $" << fixed << setprecision(2) << dailyDeposit <<  " into your account. ]" << endl;
                cout << "     [  Previous days score of " << previousDayScore << "pts added to total score. New total score: " << score << "pts. ]" << endl;
            }
        }
        delay();
    }
    // Warn player that it's getting late and Gorlock is getting tired.
    else if(hours >= 8.5)
    {
        cout << "\n";
        cout << "     [  You notice it's getting really late. ]"<< endl;
        delay(); 
    }
}

// Private member function to delay between important dialogue 
void GameStats::delay() 
{
    string next = "";
    while(next[0] != 'x')
    {
        cout << "\n[enter 'x' continue] ";
        getline(cin, next);
        cout << "\n";
    }    
}