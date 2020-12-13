// CS1300 Fall 2020
// Author: Kalid (Kal) Al-Rajhi
// Recitation: 251 – Elizabeth Spaulding
// Project3 - Own Project - Alien Ambassador
// Main Driver file 
// TO RUN: g++ alienAmbassadorGame.cpp Alien.cpp Talk.cpp GameStats.cpp Food.cpp FoodMenu.cpp Word.cpp

#include "GameStats.h"
#include "Alien.h"
#include "Talk.h"
#include "Food.h"
#include "FoodMenu.h"
#include "Word.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// ** HELPER FUNCTIONS **
int split(string text, char delimiter, vector<string> &splitText);
void displayNeeds(Alien alienLeader); // [used to debug game]
bool winConditions(Alien alienLeader, GameStats gameStats);
void delay(); // Flow control
string choice(); // Flow control
string validateOption();

// ** FILE I/O FUNCTIONS ** (functions that read (or 'loads') files into vectors before entering main game loop and one function to write scores into scores.txt)
int loadTalk(string fileName, vector<Talk> &talks);
int loadFood(string fileName, vector<Food> &foods);
int loadWord(string fileName, vector<Word> &words);
int writeScore(GameStats gameStats); 

// ** MENU FUNCTIONS ** (functions that correspond to in-game menu options)
void difficultyMenu(Alien &alienLeader, GameStats &gameStats);
void talkMenu(vector<Talk> talks, Alien &alienLeader, GameStats &gameStats);
bool talkInteraction(vector<Talk> talks, string topic, Alien &alienLeader, GameStats &gameStats);
void visitMessHall(FoodMenu foodMenu, vector<Food> foods, Alien &alienLeader, GameStats &gameStats);
void visitRumpusRoom(vector<Word> words, Alien &alienLeader, GameStats &gameStats);
bool wordGuessGame(vector<Word> words, Alien &alienLeader, GameStats &gameStats);
bool diceGame(Alien &alienLeader, GameStats &gameStats);
int diceRoll();
void robberyEncounter(Alien &alienLeader, GameStats &gameStats);

// ** ORGANIZATIONAL ** (functions that are 'display' focused and would clutter the main() function)
void gameIntro(Alien &alienLeader, GameStats &gameStats);
void gameOutro(Alien alienLeader, GameStats gameStats);
void gameInstructions();


// ** MAIN FUNCTION ** 
int main()
{
    // Seed all calls to random function
    srand(time(NULL));
    
    /* Load Content and Initialize Objects */
    // Load Talk objects
    vector<Talk> talks;
    int numOfTalkingPoints = loadTalk("talk.txt", talks);
    // Load Food objects
    vector<Food> foods;
    int numOfFoods = loadFood("food.txt", foods);
    // Load Word object
    vector<Word> words;
    int numOfWords = loadWord("word.txt", words);

    // Instantite other game objects: game stats, alien leader, etc...
    GameStats gameStats = GameStats();
    Alien alienLeader = Alien();
    FoodMenu foodMenu = FoodMenu();

    /* Initial Game Prompt */
    cout << "\n\n** WELCOME TO... **" << endl;
    cout << "   _____  .__  .__                   _____         ___.                                     .___             " << endl;
    cout << "  /  _  \\ |  | |__| ____   ____     /  _  \\   _____\\_ |__ _____    ______ ___________     __| _/___________  " << endl;
    cout << " /  /_\\  \\|  | |  |/ __ \\ /    \\   /  /_\\  \\ /     \\| __ \\\\__  \\  /  ___//  ___/\\__  \\   / __ |/  _ \\_  __ \\ " << endl;
    cout << "/    |    \\  |_|  \\  ___/|   |  \\ /    |    \\  Y Y  \\ \\_\\ \\/ __ \\_\\___ \\ \\___ \\  / __ \\_/ /_/ (  <_> )  | \\/ " << endl;
    cout << "\\____|__  /____/__|\\___  >___|  / \\____|__  /__|_|  /___  (____  /____  >____  >(____  /\\____ |\\____/|__|    " << endl;
    cout << "        \\/             \\/     \\/          \\/      \\/    \\/     \\/     \\/     \\/      \\/      \\/              " << endl;

    /* Game Instructions */
    cout << "\n";
    cout << "Would you like to read the game instructions?" << endl;

    // Yes - continue to instructions
    if(choice() == "y")
    {
        gameInstructions();
    }
    
    /* Input Name */
    cout << "\nPlease type your ambassador name: ";
    string name;
    getline(cin, name);
    gameStats.setPlayerName(name);

    /* Choose Difficulty */
    cout << "\n";
    difficultyMenu(alienLeader, gameStats);

    /* Game Introduction */
    cout << "\n";
    cout << "Would you like to go through the story introduction?" << endl;

    // Yes - continue to intro
    if(choice() == "y")
    {
        gameIntro(alienLeader, gameStats);
        cout << "\n";
        cout << alienLeader.getName() << ": Let's get acquainted!" << endl;
    }
    // No - skip intro
    else
    {
        cout << "\n";
        cout << "     [ You have " << gameStats.getMaxDays() << " days to present the peace treaty. Earn Gorlock's confidence for at least 3 days before presenting the treaty. ]" << endl;
        delay();
        cout << "     [ You follow Gorlock into the headquarters...and so your mission begins. ]" << endl;
        delay();
        cout << alienLeader.getName() << ": Welcome to Sumac9 " << "Ambassador " << gameStats.getPlayerName() << ". Lets get to know each other!" << endl;
    }
    delay();

    /* Main Game Loop */
    bool quit = false;

    while(!quit && !gameStats.getGameOver())
    {
        cout << alienLeader.getName() << ": What should we do?" << endl;
        delay();
        
        // Display main decision menu
        cout << "\n" << setfill('=') << setw(20) << "| MAIN ROOM |" << setfill('=') << setw(20) << '=' << endl;
        cout << "\n1. Check computer log" << endl;
        cout << "2. Talk" << endl;
        cout << "3. Visit Mess Hall" << endl;
        cout << "4. Visit Rumpus Room" << endl;
        cout << "5. Rest for the day" << endl;
        cout << "6. Make peace offer" << endl;
        cout << "7. Give up" << endl;
        cout << setfill('=') << setw(40) << '=' << endl;
        
        // Prompt user for option choice
        string option = validateOption();
        
        switch(stoi(option))
        {
            // Check computer log
            case 1:
            {
                cout << "\n";
                cout << "     [ You pull out your UNE certified computer log. ]" << endl;
                // Access game log, which shows relevant stats. Doesn't count as interaction.
                gameStats.displayStats();
                delay();

                // Pay 'hacker' to get Gorlock's bio stats - reveals important attributes.
                double hackCost = 0;
                if(gameStats.getDifficulty() == "Easy"){hackCost = 5.00;} // Easy
                else if(gameStats.getDifficulty() == "Normal"){hackCost = 10.00;} // Normal
                else {hackCost = 15.00;} // Difficult
                
                cout << "Computer Log: Would you like to pay a hacker $" << fixed << setprecision(2) << hackCost << " to get into Gorlock's current bio stats?" << endl;
                if(choice() == "y")
                {
                    // check if player has sufficient funds
                    if(gameStats.getMoney() >= hackCost)
                    {
                        cout << "Computer Log: ** Payment Accepted ** Here are the results..." << endl;
                        gameStats.spendMoney(hackCost);
                        delay();
                        displayNeeds(alienLeader);
                        // Pass time if player employs hacker
                        gameStats.passTime(alienLeader, 0.5);
                    }
                    else
                    {
                        cout << "Computer Log: ** Insufficient Funds **" << endl;
                    } 
                }
                delay();
                cout << "Computer Log: ** Shutting Down **" << endl;
                cout << "\n";
                cout << "     [ You put away your computer log. ]" << endl;
                delay();
                break;
            }
            // Talk
            case 2:
            {
                // Access dialogue menu
                talkMenu(talks, alienLeader, gameStats);
                break;
            }
            // Visit Mess Hall
            case 3:
            {
                // Access mess hall menu
                visitMessHall(foodMenu, foods, alienLeader, gameStats);
                break;
            }
            // Visit Rumpus Room
            case 4:
            {
                // Check energy level
                // Not enough energy to play
                if(alienLeader.getEnergy() < 20)
                {
                    cout << "\n";
                    cout << "I am a little too tired to play in the Rumpus Room." << endl;
                    delay();
                }
                // Enough energy to play
                else
                {
                    // Games and cacophony - enter the Rumpus Room!
                    visitRumpusRoom(words, alienLeader, gameStats);
                }
                break;
            }
            // Rest for the day
            case 5:
            {   
                // Rest (set energy to 100), doesn't count at interaction - player is encouraged to reast before 10 hours is up, otherwise penalized
                cout << "\n";
                cout << "     [ You propose a rest for the day. ]" << endl;
                delay();
                // If late in the day or Gorlock energy level below 50 - he'll rest
                if(gameStats.getHours() >= 8.0 || alienLeader.getEnergy() <= 50)
                {
                    // respond that it's late
                    if(gameStats.getHours() >= 8.0)
                    {
                        cout << alienLeader.getName() << ": Good idea, it's getting late." << endl;
                    }
                    // response that he's tired
                    if(alienLeader.getEnergy() <= 50)
                    {
                        cout << alienLeader.getName() << ": I am also really tired." << endl;
                    }
                    delay();
                    cout << "     [ You both go rest for the day. ]" << endl;
                    delay();

                    // Reset time stats to match rest
                    gameStats.passTime(alienLeader, 0, true);
                    
                    // Make sure it's not the past the last day
                    // Good mood/bad mood response
                    if(alienLeader.getMood() >= 50 && (gameStats.getDays() < gameStats.getMaxDays() + 1))
                    {
                        // Good mood
                        cout << alienLeader.getName() << ": Hey you're up! Let's get the day started." << endl;
                    }
                    else if(gameStats.getDays() < gameStats.getMaxDays() + 1)
                    {
                        // Bad mood
                        cout << alienLeader.getName() << ": Let's get moving you lazy glump!" << endl;
                    } 
                }
                // Neither late nor tired
                else
                {
                    // Good mood/bad mood response
                    if(alienLeader.getMood() >= 30)
                    {
                        // Good mood
                        cout << alienLeader.getName() << ": There is still time to burn and I am not even that tired!" << endl;
                    }
                    else
                    {
                        // Bad mood
                        cout << alienLeader.getName() << ": The idea of passing out and not having to spend more time with you is tempting, but there is more time to the day and I am not that tired..." << endl;
                    } 
                }
                delay();
                break;
            }
            // Make Peace offer
            case 6:
            {
                // General Dialogue 
                cout << "\n";
                cout << "     [ You ask Gorlock to sit at a nearby table. ]" << endl;
                delay();
                cout << alienLeader.getName() << ": What's going on?" << endl;
                delay();
                cout << "     [ You pull out an elegant piece of parchment gently yellowed with age and adorned with a golden seal. You hand it to Gorlock. ]" << endl;
                delay();
                cout << "Ambassador " << gameStats.getPlayerName() << ": It's a peace treaty. I believe it is time that Earth and Sumac9 end the war in favor of peace." << endl;
                delay();
                cout << "     [ Gorlock breaks the seal and begins to reads over the treaty... ]" << endl;
                delay();

                // if win conditions met, victory!
                if(winConditions(alienLeader, gameStats))
                {
                    // End game - win scenario
                    gameStats.setWin(true);
                    delay();
                    cout << "     [ Gorlock begins to tear up... ]" << endl;
                    delay();
                    cout << alienLeader.getName() << ": ...I am sorry..." << endl;
                    delay();
                    cout << alienLeader.getName() << ": this is wholly unexpected, but very much needed. It's time for this absurd war between Earth and Sumac9 to finally end. You've been good to me Ambassador " << gameStats.getPlayerName() << "." << endl;
                    delay();
                    cout << alienLeader.getName() << ": I think it's time for you to leave, I have a lot of work to do to announce the peace treatise and dismantle the M.E.G.G.U.H. Cannon. Once the dust has settled I'd love to have you back for more fun! Thank you Friend." << endl;
                    delay();
                    cout << "     [ Gorlock send you off with a headbutt and directions to your ship. ]" << endl;
                }
                // Win conditions not met
                else
                {                                
                    // End game - lose scenario
                    gameStats.setWin(false);
                    delay();
                    cout << "     [ Gorlock looks up at you with rage in his eyes... ]" << endl;
                    delay();
                    cout << alienLeader.getName() << ": ...I am sorry..." << endl;
                    delay();
                    cout << alienLeader.getName() << ": but you've been a poor guest and frankly I believe most humans are like that. It's time for you to go Ambassador " << gameStats.getPlayerName() << ". You've caused enough offense." << endl;
                    delay();
                    cout << "     [ Gorlock directs you to your ship. ]" << endl;
                }            
                delay();
                gameStats.setGameOver(true);
                break;
            }
            // Give up 
            case 7:
            {
                cout << "\n";
                cout << "     [ You let Gorlock know that you're ready to leave. ]" << endl;
                delay();
                cout << "\n" << alienLeader.getName() << ": Farewell Ambassador " << gameStats.getPlayerName() << ". I hope I didn't offend you..." << endl;
                delay();

                // Lose impression points for quitting early
                alienLeader.setImpression(alienLeader.getImpression() - 50);
                
                // End game - lose scenario (peace treaty not offered)
                gameStats.setWin(false);
                gameStats.setGameOver(true);
                break;
            }
            // Invalid input
            default:
            {
                cout << "\n" << alienLeader.getName() << ": I don't understand, can you repeat that?" << endl;
                delay();
                break;
            }
        }
    }
    
    /* End Game */
    gameOutro(alienLeader, gameStats);

    // Game Over prompt
    cout << "\n\n";
    cout << "  ________                      ________                      " << endl;
    cout << " /  _____/_____    _____   ____ \\_____  \\___  __ ___________  " << endl;
    cout << "/   \\  ___\\__  \\  /     \\_/ __ \\ /   |   \\  \\/ // __ \\_  __ \\ " << endl;
    cout << "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___//    |    \\   /\\  ___/|  | \\/ " << endl;
    cout << " \\______  (____  /__|_|  /\\___  >_______  /\\_/  \\___  >__|    " << endl;
    cout << "        \\/     \\/      \\/     \\/        \\/          \\/        " << endl;
    cout << "\n";
    delay();  
    
    // Record score and score details
    writeScore(gameStats);

    // Display end game stats
    gameStats.displayStats();
    cout << "[[ Name, Difficulty, Days, Interactions, Money, and Score recorded in scores.txt ]]" << endl;
    delay();

    return 0;
}


// ** HELPER FUNCTIONS **
/** Function that splits a string into substrings designated by a delimiter and returns the number of times it split
 * @param string of text to be broken up by delimeter
 * @param char delimeter 
 * @param vector <string> to store seperated words
 * @return int number of splits
*/
int split(string text, char delimiter, vector<string> &splitText)
{
    int splitCount = 0;
    string word = "";

    // if text is blank, return split count of 0
    if (text == "")
    {
        return splitCount;
    }
    
    // Loop through text, stopping at each delimiter.
    for (int i = 0; i <= text.length(); i++)
    {
        // check for delimiter or last letter then store word
        if (text[i] == delimiter || i == text.length())
        {
            // Store current word into splitText array
            splitText.push_back(word);
            // Increment split count
            splitCount++;            
            // reset word to blank
            word = "";
            
            // Keep skipping blank spaces of text after delimeter (ex Genre,' 'Author)
            int j = i + 1;
            while(text[j] == ' ')
            {
                i++;
                j = i + 1;
            }
        }
        else
        {
            // form word char by char - reset when delimiter found
            word += text[i];
        }
    }

    // error: if no delimeter found, return 1
    if (splitCount == 0 && text != "")
    {
        return 1;
    }
    // error: if the number of words is greater than the size of the vector, return -1
    if (splitCount > splitText.size())
    {
        return -1;
    }

    return splitCount;
}

/** Function to check alien's needs (private data members)
 * @param Alien leader object to check stats
 */
void displayNeeds(Alien alienLeader)
{
    cout << "\n" << setfill('#') << setw(50) << "| GORLOCK'S BIO STATS |" << setw(30) << '#' << endl;
    cout << "\n";
    cout << "   Nourishment: " << alienLeader.getNourishment() << "/100" << endl;
    cout << "   Fun: " << alienLeader.getFun() << "/100" << endl;
    cout << "   Energy: " << alienLeader.getEnergy() << "/100" <<  endl;
    cout << "   Impression: " << alienLeader.getImpression() << "/300" << endl;
    cout << "   Mood: " << alienLeader.getMood() << "%" << endl;
    cout << "\n";
    cout << setfill('#') << setw(80) << '#' << endl;
}

/** Function to check if victory criteria met
 * @param Alien leader object to check stats
 * @param GameStats object to check stats
 * @return bool - true if player met ALL win conditions, false otherwise.
 */
bool winConditions(Alien alienLeader, GameStats gameStats)
{
    // must fulfill all 4 conditions
    int conditionCount = 0;
    
    cout << "[ ** lose conditions: ";
    // Check if min day met
    if(gameStats.getDays() > 2)
    {
        conditionCount++;
    }
    else{cout << " 1 or 2 DAY(S) TOO SOON...";}
    // Check if min mood met
    if(alienLeader.getMood() >= 50)
    {
        conditionCount++;
    }
    else{cout << " Gorlock is not in the right MOOD...";}
    // Check if min impression met
    if(alienLeader.getImpression() >= 150)
    {
        conditionCount++;
    }
    else{cout << " Gorlock is not IMPRESSED by you...";}
    // Check if more positive interactions than negative interactions
    if(gameStats.getPositiveInteractions() > gameStats.getNegativeInteractions())
    {
        conditionCount++;
    }
    else{cout << " You had more negative interactions than positive interactions with Gorlock...";}

    // if above condition met or exceeded, return true for victory
    if(conditionCount == 4)
    {
        cout << "NONE - all conditions met! ** ]";
        return true;
    }
    // else return false 
    else
    {
        cout << " - conditions NOT met. ** ]" << endl;
        return false;
    }  
}

/** Function to delay between important dialogue of game
 */
void delay()
{
    string next = "";
    while(next[0] != 'x')
    {
        cout << "\n[enter 'x' continue] ";
        getline(cin, next);
        cout << "\n";
    }    
}

/** Function that asks a user for a 'y' or 'n' choice
 * @return string 'y' or 'n' value
 */
string choice()
{
    bool validChoice = false;
    string choice = "";
    while(!validChoice)
    {
        cout << "\n[enter 'yes' or 'no'] ";
        getline(cin, choice);
        cout << "\n";
        if(tolower(choice[0]) == 'y')
        {
            choice = "y";
            validChoice = true;
        }
        else if(tolower(choice[0]) == 'n')
        {
            choice = "n";
            validChoice = true;
        }
        else
        {
            cout << "[** invalid choice **]" << endl;
        }
    }
    return choice;
}

/** Function that asks a user for a number option 0-9 when typcasting a string
 * @return string 0-9
 */
string validateOption()
{
    string option = "";
    int num = -1;
    // String with ASCII Number between 0 and 9
    bool done = false;
    while(!done) 
    {
        cout << "Option Number: ";
        getline(cin, option);

        if(((int)option[0] >= (int)'0' && (int)option[0] <= (int)'9'))
        {
            done = true;
        }
        else
        {
            cout << "Invalid Option - please input an integer." << endl;
        }
    }
    return option;
}


// ** FILE I/O FUNCTIONS **
/** Function that reads a file and stores data as a 'talk'. So Convo Topic, Player Says, Alien Response (pos), Alien Response (neg)
 * @param string name of input file/file to read from
 * @param Talk array of Talk objects
 * @return int number of talks stored
*/
int loadTalk(string fileName, vector<Talk> &talks)
{
    // Open File
    ifstream inFile(fileName);
    
    // Check if opened
    if(inFile.fail()){return -1;}
    
    // Read data file line by line
    string line = "";
    int objectIdx = 0;
    
    // Skip first line
    getline(inFile, line);

    while(getline(inFile, line))
    {
        // Skip empty lines
        if(line == "")
        {
            continue;
        }
        // temp vector to collect each talk object's respective Convo Topic, Player Says, Alien Response (pos), Alien Response (neg)
        vector<string> talkDetails;
        // Split up line
        split(line, '|', talkDetails);
        
        // Set each talk object its respective [0]Convo Topic, [1]Player Says, [2]Alien Response (pos), [3]Alien Response (neg) via overloaded constructor
        talks.push_back(Talk(talkDetails[0], talkDetails[1], talkDetails[2], talkDetails[3]));

        // Move on to next talk object
        objectIdx++;
    }
    inFile.close();
    
    // Return number of talks stored
    return talks.size();
}

/** Function that reads a file and stores data as a 'food'. 
 * @param string name of input file/file to read from
 * @param Food vector of Food objects
 * @return int number of foods stored
*/
int loadFood(string fileName, vector<Food> &foods)
{
    // Open File
    ifstream inFile(fileName);
    
    // Check if opened
    if(inFile.fail()){return -1;}
    
    // Read data file line by line
    string line = "";
    int objectIdx = 0;
    
    // Skip first line
    getline(inFile, line);

    while(getline(inFile, line))
    {
        // Skip empty lines
        if(line == "")
        {
            continue;
        }
        // temp vector to collect each Food object's details
        vector<string> foodDetails;
        // Split up line
        split(line, ',', foodDetails);
        
        // Set each food object its respective [0]Type, [1]Name, [2]Cost, [3]Calories via overloaded constructor
        foods.push_back(Food(foodDetails[0], foodDetails[1], stod(foodDetails[2]), stoi(foodDetails[3])));

        // Move on to next Food object
        objectIdx++;
    }
    inFile.close();
    
    // Return number of foods stored
    return foods.size();
}

/** Function that reads a file and stores data as a 'word'. 
 * @param string name of input file/file to read from
 * @param Word array of Word objects
 * @return int number of Words stored
*/
int loadWord(string fileName, vector<Word> &words)
{
    // Open File
    ifstream inFile(fileName);
    
    // Check if opened
    if(inFile.fail()){return -1;}
    
    // Read data file line by line
    string line = "";
    int objectIdx = 0;
    
    // Skip first line
    getline(inFile, line);

    while(getline(inFile, line))
    {
        // Skip empty lines
        if(line == "")
        {
            continue;
        }
        // temp vector to collect each Word object's details
        vector<string> wordDetails;
        // Split up line
        split(line, ',', wordDetails);
        
        // Set each Word object its respective [0]word, [1]clue for word via overloaded constructor
        words.push_back(Word(wordDetails[0], wordDetails[1]));

        // Move on to next Word object
        objectIdx++;
    }
    inFile.close();
    
    // Return number of words stored
    return words.size();
}

/** Function writes to a file with scores
 * @param GameStats object to extract score, name, and difficulty
 * @returns a non-zero number if failed
 */
int writeScore(GameStats gameStats)
{
    // Input scores into file - create output stream object
    ofstream outFile;
    
    // Open in append mode
    outFile.open("scores.txt", fstream::app);

    // Check if opened
    if(outFile.fail()){return -1;}
    
    // Input score info as name, difficulty, number of days, number of interactions, $ left, final score
    outFile << "Ambassador " << gameStats.getPlayerName() << ", " << gameStats.getDifficulty() << ", " 
            << gameStats.getDays() << ", " << gameStats.getTotalInteractions() << ", $" << gameStats.getMoney() << ", " << gameStats.getScore() << endl;
    
    // Close file
    outFile.close();
    return 0;
}


// ** MENU FUNCTIONS **
// || DIFFICULTY MENU ||
void difficultyMenu(Alien &alienLeader, GameStats &gameStats)
{
    bool selectionMade = false;
    while(!selectionMade)
    {
        cout << "Choose your difficulty: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Normal" << endl;
        cout << "3. Difficult" << endl;
        string option;
        getline(cin, option);
        if(option == "1" || option == "2" || option == "3" )
        {
            // Set difficulty
            gameStats.setDifficulty(alienLeader, stoi(option));
            selectionMade = true;
        }
    }
}

/** Function takes player into the submenu 'Talk' with many interaction options
 * (Main Room Option 2 - Talk)
 * @param vector<Talk> objects full of different pre-written convo topics
 * @param Alien to use object methods
 * @param GameStats to use object methods
*/
void talkMenu(vector<Talk> talks, Alien &alienLeader, GameStats &gameStats)
{
    cout << "\n";
    cout << "     [ You and Gorlock grab a seat on a nearby couch. ]" << endl;
    delay();
    bool quit = false;
    while(!quit && !gameStats.getGameOver())
    {
        // Check if first interaction of day 
        bool firstInteraction = false;
        if(gameStats.getHours() == 0.0)
        {
            cout << "     [ Neither of you have said anything to each other yet... ]" << endl;
            firstInteraction = true;
        }
        else{cout << alienLeader.getName() << ": What's on your mind?" << endl;}
        delay();

        // Display TALK MENU options
        cout << "\n" << setfill('=') << setw(20) << "| TALK |" << setfill('=') << setw(20) << '=' << endl;
        cout << "\n1. Ice breaker" << endl; // only useful if it's the first thing you say
        cout << "2. Casual conversation" << endl; 
        cout << "3. Compliment" << endl; 
        cout << "4. Tell a joke" << endl;
        cout << "5. Listen" << endl; // a data base of random sayings (gives clues to what he likes- also when hes asleep)
        cout << "6. Offer a headbutt" << endl; 
        cout << "7. Done Talking" << endl;
        cout << setfill('=') << setw(40) << '=' << endl;

        // Prompt user for option
        string option = validateOption();

        // Interaction options
        bool positiveInteraction = true;
        switch(stoi(option))
        {
            case 1:
            {                              
                cout << "\n";
                cout << "     [ Things are a little quiet, so you break the ice by saying... ]" << endl;
                delay();

                // Search for talk object with topic 'ice breaker'
                string subject = "ice breaker";
                positiveInteraction = talkInteraction(talks, subject, alienLeader, gameStats);
                
                // Reward player if first interaction is an ice breaker
                int modifier = 0;
                if(firstInteraction)
                {
                    cout << "\n";
                    cout << alienLeader.getName() << ": Glad you broke the ice, I hate being the first to open my mouth - unless I am eating!" << endl;
                    modifier = 10;
                }
                alienLeader.talkPreferences(positiveInteraction, subject, modifier);
                
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                gameStats.passTime(alienLeader, 1);
                break;
            }
            case 2:
            {
                cout << "\n";
                cout << "     [ You slouch a bit and begin to speak... ]" << endl;
                delay();                
                // Search for talk object with topic 'casual'
                string subject = "casual";
                positiveInteraction = talkInteraction(talks, subject, alienLeader, gameStats);
                alienLeader.talkPreferences(positiveInteraction, subject);
                
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                gameStats.passTime(alienLeader, 2);
                break;
            }
            case 3:
            {                
                cout << "\n";
                cout << "     [ You try to think of something nice to say... ]" << endl;
                delay();
                // Search for talk object with topic 'compliment'
                string subject = "compliment";
                positiveInteraction = talkInteraction(talks, subject, alienLeader, gameStats);
                alienLeader.talkPreferences(positiveInteraction, subject);
                
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                gameStats.passTime(alienLeader, 1.5);
                break;
            }
            case 4:
            {
                cout << "\n";
                cout << "     [ You lift your left eye brow up, grin, and prepare to tell a joke... ]" << endl;
                delay();
                // Search for talk object with topic 'joke'
                string subject = "joke";
                positiveInteraction = talkInteraction(talks, subject, alienLeader, gameStats);
                alienLeader.talkPreferences(positiveInteraction, subject);
                
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                gameStats.passTime(alienLeader, 1.5);
                break;
            }
            case 5:
            {
                cout << "\n";
                cout << "     [ You get closer to Gorlock and check-in... ]" << endl;
                delay();

                // Search for talk object with topic 'listen'
                string subject = "listen";
                positiveInteraction = talkInteraction(talks, subject, alienLeader, gameStats);
                alienLeader.talkPreferences(positiveInteraction, subject);
                
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                gameStats.passTime(alienLeader, 3);
                break;
            }
            case 6:
            {
                // Headbutt (bonus points if headbutt within last hour of day)
                cout << "\n";
                cout << "     [ You pull up to Gorlock and swing your head into his. ]" << endl;
                delay();
                // Headbutt resolution
                bool positiveInteraction = true;
                int modifier = 0;
                if(gameStats.getHours() >= 9.0)
                {
                    modifier = 10;
                    alienLeader.talkPreferences(positiveInteraction, "headbutt", modifier); 
                    gameStats.passTime(alienLeader, 1);
                }
                else
                {
                    positiveInteraction = false;
                    modifier = 5;
                    alienLeader.talkPreferences(positiveInteraction, "headbutt", modifier);  
                    gameStats.passTime(alienLeader, 0.50);
                }
                // Update game stats
                gameStats.interactionCount(positiveInteraction);
                break;
            }
            case 7:
            {
                cout << "\n";
                cout << alienLeader.getName() << ": Good talk." << endl;
                delay();
                cout << "     [ You and Gorlock get off the couch. ]" << endl;
                quit = true;
                break;
            }
            default:
                cout << alienLeader.getName() << ": Sorry, I don't understand what you're saying. Can you repeat that?" << endl;

        }
        delay();
    }
}

/** Function returns a random conversation related to given topic and mood of alien
 * @param vector<Talk> of Talk objects
 * @param string topic
 * @return bool true if positive interaction, negative otherwise
 */
bool talkInteraction(vector<Talk> talks, string topic, Alien &alienLeader, GameStats &gameStats)
{   
    bool positiveInteraction = true;
    // Keep searching for a random thing to say related to topic
    int i = 0;
    bool found = false;
    // Interaction - player speaks, alien responds
    cout << setfill('-') << setw(100) << '-' << endl;
    while(!found)
    {
        // Random num between 0 to size of vector
        i = rand() % talks.size();
        // Match topic
        if(talks[i].getTopic() == topic)
        {
            cout << "\n" << gameStats.getPlayerName() << ": " << talks[i].getPlayerSays() << endl;
            found = true;
        }
    }
    // Positive response
    if(alienLeader.getMood() > 40)
    {
        cout << "\n" << alienLeader.getName() << ": " << talks[i].getPosResponse() << endl;
        cout << "\n" << setfill('-') << setw(100) << '-' << endl;
        return positiveInteraction;
    }
    // Negative response
    else
    {
        cout << "\n" <<  alienLeader.getName() << ": " << talks[i].getNegResponse() << endl;
        cout << "\n" << setfill('-') << setw(100) << '-' << endl;
        positiveInteraction = false;
        return positiveInteraction;
    }
}

/** Function takes player into the submenu 'Mess Hall' with many interaction options
 * (Main Room Option 3 - Visit Mess Hall)
 * @param foodMenu to use object methods for displaying/interacting with Food objects
 * @param vector<Food> objects full of Food stats
 * @param Alien to use object methods
 * @param GameStats to use object methods
*/
void visitMessHall(FoodMenu foodMenu, vector<Food> foods, Alien &alienLeader, GameStats &gameStats)
{
    // Prompt user they've entered Mess Hall
    cout << "\n";
    cout << "     [ You and Gorlock enter the Mess Hall ]" << endl;
    delay();

    // Mess Hall Loop
    bool quit = false;
    while(!quit && !gameStats.getGameOver())
    {
        // Check if first interaction of day 
        if(gameStats.getHours() == 0.0)
        {
            cout << alienLeader.getName() << ": Breaking the ice with a trip to the Mess Hall? Hmmm..." << endl;
            alienLeader.setImpression(alienLeader.getImpression() - 5);
            delay();
        }

        // Check for random encounter (getting robbed)
        robberyEncounter(alienLeader, gameStats);

        // Display MESS HALL options
        cout << "\n" << setfill('=') << setw(20) << "| MESS HALL |" << setfill('=') << setw(20) << '=' << endl;
        cout << "\n1. Order food" << endl;
        cout << "2. Pick a fight" << endl; 
        cout << "3. Exit Mess Hall" << endl; 
        cout << setfill('=') << setw(40) << '=' << endl;
        
        // Prompt user for option
        string option = validateOption();
        
        // Interaction options
        bool positiveInteraction = true;
        switch(stoi(option))
        {
            // Food Menu - displays menu of food items depending on time of day
            case 1:
            {              
                cout << "\n";
                cout << "     [ A giant screen bot approaches your table to take your order ]" << endl;
                delay();
                // Display food menu and order 
                int foodOrderIdx = foodMenu.orderFood(gameStats.getHours(), foods);
                
                delay();
                // Check if order canceled or place is closed
                if(foodOrderIdx < 0)
                {
                    
                    // Player encountered 'closed' sign
                    if(foodOrderIdx == -1)
                    {
                        cout << alienLeader.getName() << ": Looks like they're closed..." << endl;
                    }
                    // Player canceled menu order
                    else
                    {
                        cout << alienLeader.getName() << ": Didn't find what you wanted?" << endl;
                    }
                    delay();
                    gameStats.passTime(alienLeader, 0.50);
                    break;
                }                
                // Check if user has enough funds
                bool enoughFunds = gameStats.spendMoney(foods[foodOrderIdx].getCost());
                if(enoughFunds)
                {
                    // Alien leader will share his preferences based off the name of the food ordered (effects impression)
                    bool likesFoodOrder = alienLeader.foodPreferences(foods[foodOrderIdx].getName());

                    // Nourishment level greater than 80%, leader will not like eating a full meal. Also, if he didn't like that food
                    if(alienLeader.getNourishment() > 80 || !likesFoodOrder)
                    {
                        // Response for both full and poor food choice
                        if(alienLeader.getNourishment() > 80 && !likesFoodOrder)
                        {
                            cout << alienLeader.getName() << ": I am too full to eat this garbage." << endl;
                            positiveInteraction = false;
                            gameStats.passTime(alienLeader, 1.5);
                        }
                        // Response for just full
                        else if(alienLeader.getNourishment() < 90)
                        {
                            cout << alienLeader.getName() << ": hmmm...I am pretty stuffed, but I can fit a bit more." << endl;
                            alienLeader.Eat(foods[foodOrderIdx].getCalories());
                            positiveInteraction = true;
                            // full, so longer time to eat than when hungry
                            gameStats.passTime(alienLeader, 2.5);
                        }
                        // Response for too full
                        else if(alienLeader.getNourishment() < 95)
                        {
                            cout << alienLeader.getName() << ": Stop asking me to eat, I am well nourished." << endl;
                            alienLeader.Eat(foods[foodOrderIdx].getCalories());
                            positiveInteraction = false;
                            gameStats.passTime(alienLeader, 1.5);
                        }
                        // Response for not liking the food item
                        else
                        {
                            cout << alienLeader.getName() << ": I am not eating this..." << endl;
                            positiveInteraction = false;
                            gameStats.passTime(alienLeader, 1.5);
                        }
                    }
                    // Alien leader hungry, so eats as a positive interaction;
                    else
                    {
                        cout << alienLeader.getName() << ": My hunger makes this meal taste so much better." << endl;
                        alienLeader.Eat(foods[foodOrderIdx].getCalories());
                        positiveInteraction = true;
                        gameStats.passTime(alienLeader, 2);
                    }
                }
                else
                {
                    cout << alienLeader.getName() << ": Do you expect ME to pay!?" << endl;
                    positiveInteraction = false;
                    gameStats.passTime(alienLeader, 0.5);
                }
                // Check if overall interaction positive or negative
                gameStats.interactionCount(positiveInteraction);
                delay();
                break;             
            }
            // Fight - a game of chance. Brawl with someone in the Mess Hall, if you win you impress Gorlock - otherwise you go home in a stretcher (end game)
            case 2:
            {           
                cout << "\n";
                cout << "     [ You notice a short, but stout Dwarf looking man staring at you - it's a Forlatian trooper ready for a brawl. ]" << endl;
                delay();
                cout << "     [ The closer you get, the larger he gets - this might be harder than you expected... ]" << endl;
                delay();
                cout << "     [ Do you want to press on for a fight? ]" << endl;
                
                if(choice() == "y")
                {
                    cout << "\n";
                    cout << "     [ You press on, approaching the Forlatian trooper with a determined look in your eyes ]" << endl;
                    delay();
                    int winChance = ((rand() % 3 - 1 + 1) + 1); // range [1,3]..so a 2/3 chance of winning a fight - high risk, high reward
                    // win 
                    if(winChance != 3)
                    {
                        cout << "     [ Just as you throw a punch, you find youself falling to the ground ]" << endl;
                        delay();
                        cout << "     [ The trooper is about to kick your head ]" << endl;
                        delay();
                        cout << "     [ You have a split second to counter - do you want to attempt a headlock? Otherwise you'll try to cover your head. ]" << endl;
                        // Attempt headlock 
                        if(choice() == "y")
                        {                                                    
                            cout << "     [ You trip the trooper and put him into a headlock. ]" << endl;
                            delay();
                            cout << "     [ He taps the floor and you release him. He runs off crying. ]" << endl;
                            delay();
                            cout << alienLeader.getName() << ": You really frightened off that Forlatian trooper! Never seen anyone use a yotalian headlock like that!" << endl;
                            delay();
                            positiveInteraction = true;
                            alienLeader.setImpression(alienLeader.getImpression() + 25);
                        }
                        // Protect head
                        else
                        {                                                    
                            cout << "     [ As the trooper lifts his foot to kick you, he slips and falls forward...hitting the ground and passes out ]" << endl;
                            delay();
                            cout << alienLeader.getName() << ": Wow! You got lucky...I guess the floor is the winner?" << endl;
                            delay();
                            positiveInteraction = true;
                            alienLeader.setImpression(alienLeader.getImpression() + 15);
                        }
                    }
                    // Lose fight
                    else
                    {
                        // Detail loss
                        cout << "     [ The trooper lifts his foot to kick you, each kick worse than the last. ]" << endl;
                        delay();
                        cout << "     [ You're in critical condition and will need to be flown to a nearby UNE medical station. ]" << endl;
                        delay();
                        cout << alienLeader.getName() << ": That Forlatian trooper really did a number on you, time for you to get off my station...weakling." << endl;
                        delay();
                        positiveInteraction = false;
                        alienLeader.setImpression(alienLeader.getImpression() - 40);
                        
                        // End game - lose scenario
                        gameStats.setWin(false);
                        gameStats.setGameOver(true);
        
                    }
                    gameStats.passTime(alienLeader, 2);
                }
                else
                {
                    cout << alienLeader.getName() << ": Darn! I was hoping to see some blood." << endl;
                    delay();
                    positiveInteraction = false;
                    alienLeader.setImpression(alienLeader.getImpression() - 5);
                    gameStats.passTime(alienLeader, 1);
                }
                // Check if overall interaction positive or negative
                gameStats.interactionCount(positiveInteraction);
                break;
            }
            case 3:
            {
                cout << "\n" << alienLeader.getName() << ": The smell of food and blood still lingers." << endl;
                delay();
                cout << "     [ You and Gorlock exit the Mess Hall ]" << endl;
                delay();
                quit = true;
                break;
            }
            default:
            {
                cout << "\n" << alienLeader.getName() << ": Sorry, what is it you want to do?" << endl;
                delay();
            }
        }
    }
}

/** Function takes player into the submenu 'Rumpus Room' with many interaction options
 * (Main Room Option 4 - Visit Rumpus Room)
 * @param vector<Word> objects full of different pre-written words to be used in word guessing game
 * @param Alien to use object methods
 * @param GameStats to use object methods
*/
void visitRumpusRoom(vector<Word> words, Alien &alienLeader, GameStats &gameStats)
{
    // Prompt user they've entered Rumpus Room
    cout << "\n";
    cout << "     [ You and Gorlock enter the Rumpus Room ]" << endl;
    delay();

    // Rumpus Room Loop
    bool quit = false;
    while(!quit && !gameStats.getGameOver())
    {
        // Check if first interaction of day 
        if(gameStats.getHours() == 0.0)
        {
            cout << alienLeader.getName() << ": I see you want start the day off in the Rumpus Room." << endl;
            alienLeader.setImpression(alienLeader.getImpression() - 5);
            delay();
        }
        // Display RUMPUS ROOM options
        cout << "\n" << setfill('=') << setw(20) << "| RUMPUS ROOM |" << setfill('=') << setw(20) << '=' << endl;
        cout << "\n1. Play 'Guess the Word'" << endl;
        cout << "2. Play Dice" << endl; 
        cout << "3. Wrestle" << endl; 
        cout << "4. Exit Rumpus Room" << endl; 
        cout << setfill('=') << setw(40) << '=' << endl;

        // Prompt user for option
        string option = validateOption();

        // Check if energy levels low, if so exit Rumpus Room (assuming player insists on playing more)
        if(alienLeader.getEnergy() < 25 && option != "4")
        {
            cout << "\n";
            cout << "     [ Gorlock steps in front of you to stop you from going any further. ]" << endl;
            delay();
            cout << alienLeader.getName() << "I am burned out - maybe we should leave and grab something to eat or get some rest." << endl;
            // Force player into 'exit' option
            option = "4";
            delay();
        }
        
        // Interaction options
        bool win = false;
        bool positiveInteraction = true;
        switch(stoi(option))
        {
            // Guess the word - guess the word Gorlock is thinking of
            case 1:
            {              
                cout << "\n";
                cout << "   [ You and Gorlock walk up to a nearby holo-board display ] " << endl;
                delay();
                
                // Play guessing game - returns win status
                win = wordGuessGame(words, alienLeader, gameStats);
                
                // Player wins, Gorlock's impression and fun go up
                if(win)
                {
                    alienLeader.setImpression(alienLeader.getImpression() + 10);
                    alienLeader.setFun(alienLeader.getFun() + 15);
                }
                // Player loses, Gorlock's impression goes down, but fun goes up a bit more than when player wins
                else
                {
                    alienLeader.setImpression(alienLeader.getImpression() - 5);
                    alienLeader.setFun(alienLeader.getFun() + 20);
                }
                // Gorlock loves games, so always a positive interaction
                alienLeader.setEnergy(alienLeader.getEnergy() - 10);
                gameStats.interactionCount(positiveInteraction);
                
                // 3 hours pass
                gameStats.passTime(alienLeader, 3.0);
                break;
            }
            // Roll Dice - gambling game, where you can earn some more $$ 
            case 2:
            {              
                cout << "\n";
                cout << "   [ You and Gorlock walk up to the gambling table. ] " << endl;
                delay();
                
                // Play dice game - returns win status
                win = diceGame(alienLeader, gameStats);
                
                // Player wins, Gorlock's impression and fun go up - not by a lot because he lost a gamble
                if(win)
                {
                    alienLeader.setImpression(alienLeader.getImpression() + 10);
                    alienLeader.setFun(alienLeader.getFun() + 5);
                }
                // Player loses, Gorlock's impression goes down, but fun goes up a bit more than when player wins
                else
                {
                    alienLeader.setImpression(alienLeader.getImpression() - 5);
                    alienLeader.setFun(alienLeader.getFun() + 10);
                }
                // Gorlock loves games, so always a positive interaction
                alienLeader.setEnergy(alienLeader.getEnergy() - 5);
                gameStats.interactionCount(positiveInteraction);
                
                // 2.5 hours pass
                gameStats.passTime(alienLeader, 2.5);
                break;
            }
            // Wrestle Gorlock - a game of chance. Brawl with Gorlock - the lower his energy, the more likely you'll win.
            case 3:
            {           
                cout << "\n";
                cout << alienLeader.getName() << ": WELCOME TO THE HALL OF PAIN!" << endl;
                delay();
                cout << "     [ Gorlock takes a wrestling stance. ]" << endl;
                delay();
                cout << "     [ Do you want to press on for a match? ]" << endl;
                
                if(choice() == "y")
                {
                    cout << "\n";
                    cout << gameStats.getPlayerName() << ": CAN YOU SMELL WHAT THE AMBASSADOR IS COOKIN'!?" << endl;
                    delay();
                    cout << "     [ You match Gorlock's stance. ]" << endl;
                    delay();
                    
                    // Determine chance of winning based off Gorlock's energy level.
                    int winChance = ((rand() % 100 - 1 + 1) + 1); // range [1, 100] 
                    // Modify win chance based off energy level - the lower Gorlock's energy the more likely the player wins. 
                    winChance -= alienLeader.getEnergy() / 5;
                    // Possible Win - 65% chance + energy modifier (so if Gorlock's energy is at 50%, your chance of winning only decreased by 10%. If he was at 100%, you chance of winning is decreased by 20%)
                    if(winChance >= 35)
                    {
                        cout << "     [ After exchanging slams, kicks, and chokes - Gorlock flies in with his final move. An aerial Moonsault slam!!! ]" << endl;
                        delay();
                        cout << "     [ You have a split second to counter - do you want to attempt to roll out of the way? Otherwise you'll try to take a defensive position. ]" << endl;
                        
                        // Attempt to roll
                        if(choice() == "y")
                        {         
                            // Determine chance of rolling out of the way successfully
                            winChance = ((rand() % 100 - 1 + 1) + 1); // range [1, 100]   
                            // Win - 70% chance 
                            if(winChance >= 40)
                            {
                                cout << "     [ You successfully roll out of the way! Gorlock body slams the floor. ]" << endl;
                                delay();
                                cout << "     [ He taps the floor and yields. ]" << endl;
                                delay();
                                cout << alienLeader.getName() << ": I almost had you! I guess you win..." << endl;
                                delay();
                                positiveInteraction = true;
                                alienLeader.setImpression(alienLeader.getImpression() + 15);
                            }
                            // rolling away fails (Gorlock is not impressed)
                            else
                            {
                                cout << "     [ You fail to roll out of the way! Gorlock body slams you like a ton of steel. ]" << endl;
                                delay();
                                cout << "     [ You tap the floor and yield. ]" << endl;
                                delay();
                                cout << alienLeader.getName() << ": HAHAHA! VICTORY! " << endl;
                                delay();
                                positiveInteraction = true;
                                alienLeader.setImpression(alienLeader.getImpression() - 5);                    
                            }
                            // Increase fun
                            alienLeader.setFun(alienLeader.getFun() + 15);
                            
                        }
                        // Defensive position
                        else
                        {                                                    
                            cout << "     [ You curl up into a defensive position. ]" << endl;
                            delay();
                            cout << "     [ Gorlock's body slams you, but the way you're curled reduces the blow and knocks the wind out of Gorlock. ]" << endl;
                            delay();
                            cout << "     [ Completely out of breath, he taps the floor and yields. ]" << endl;
                            delay();
                            cout << alienLeader.getName() << ": Gorlock points to you and labors to get out the words: W I N N E R." << endl;
                            delay();
                            positiveInteraction = true;
                            alienLeader.setImpression(alienLeader.getImpression() + 15);
                            alienLeader.setFun(alienLeader.getFun() + 10);
                        }
                    }
                    // Lose fight
                    else
                    {
                        // Detail loss
                        cout << "     [ Without warning, Gorlock slams your head with a collapsable chair. ]" << endl;
                        delay();
                        cout << "     [ You fall to the ground and immediately tap out. ]" << endl;
                        delay();
                        cout << alienLeader.getName() << ": I WIN! Sorry I wasn't more 'chair'atable...but there were no tables!!!" << endl;
                        delay();
                        positiveInteraction = true;
                        alienLeader.setImpression(alienLeader.getImpression() - 5);
                        alienLeader.setFun(alienLeader.getFun() + 5);
                    }
                    // Check if overall interaction positive or negative
                    gameStats.interactionCount(positiveInteraction);
                    gameStats.passTime(alienLeader, 2.5);
                }
                // Do no press on for a wrestling match
                else
                {
                cout << "     [ Gorlock goes back to his normal stance. ]" << endl;
                delay();
                cout << alienLeader.getName() << ": Well, maybe next time when you're feeling a bit more courageous." << endl;
                delay();
                }
                break;
            }
            // Exit Rumpus Room
            case 4:
            {
                // Exit room dialogue - move back to previous menu.
                cout << "\n" << alienLeader.getName() << ": That was fun." << endl;
                delay();
                cout << "     [ You and Gorlock exit the Rumpus Room ]" << endl;
                delay();
                quit = true;
                break;
            }
            // Invalid input
            default:
            {
                cout << "\n" << alienLeader.getName() << ": Sorry, what is it that you want to do in here?" << endl;
                delay();
            }
        }
    }
}

/** Function simulates a word guessing game 
 * @param vector<Word> objects to choose from for guessing.
 * @param Alien to use object methods
 * @param GameStats to use object methods
 * @return bool if player won or not.
*/
bool wordGuessGame(vector<Word> words, Alien &alienLeader, GameStats &gameStats)
{
    // Display Instructions
    cout << "\n";
    cout << "   [ The holo-board displays the following instructions... ] " << endl;
    delay();
    cout << "\n" << setfill('*') << setw(50) << "| GUESS THE WORD INSTRUCTIONS |" << setfill('*') << setw(20) << '*' << endl;
    cout << "\n1) Gorlock will pick a random word." << endl;
    cout << "2) The player has 10 chances to guess the letter and 1 chance to guess the word." << endl;
    cout << "3) The player can ask for a clue, but it costs 2 chances and player must have at least 3 chances." << endl;
    cout << "4) If the player reveals the word in under 10 guesses OR guesses the word correctly, they WIN. Otherwise they LOSE." << endl;
    cout << "\n" << setfill('*') << setw(70) << '*' << endl;
    delay();

    // Random num between 0 to size of vector
    int wordIdx = rand() % words.size();

    // Get random word
    string wordToGuess = words[wordIdx].getWord();
    string clue = words[wordIdx].getClue();

    // Announce word chosen
    cout << "\n";
    cout << alienLeader.getName() << ": Okay! I've chosen a word. Good luck Ambassador." << endl;
    delay();

    // Set-up display word (which player will slowly reveal)
    string displayWord = "";
    // Blank lines length of word to guess
    for(int i = 0; i < wordToGuess.length(); i++)
    {
        displayWord += '_';
    }

    // Guessing Game Loop
    const int MAX_GUESSES = 10;
    int numOfGuesses = 0;
    bool wordFound = false;
    bool done = false;
    // Only one chance to guess the word
    string wordGuess = "";
    while(!done)
    {
        // Update current board and display
        cout << "\nNumber of Guesses Left: " << (MAX_GUESSES - numOfGuesses) << endl;
        for(int i = 0; i < wordToGuess.length(); i++)
        {
            cout << displayWord[i] << " ";
        }
        cout << "\n";

        bool validGuess = false;
        // Ask player for guess or clue loop
        while(!validGuess)
        {
            cout << "\nGuess a letter (type '?' for a clue or '#' to guess the whole word): ";
            string letterGuess = "";
            getline(cin, letterGuess);

            // Check if player wants a clue and has enough guesses left (3 less than max alloted guesses)
            if(letterGuess[0] == '?' && numOfGuesses <= (MAX_GUESSES - 3))
            {
                cout << "\nClue: " << clue << endl;
                numOfGuesses += 2;
                continue;
            }
            else if(letterGuess[0] == '?')
            {
                cout << "\n";
                cout << "   [ You need at least 3 guesses left to get a clue. ] " << endl;
                continue;
            }
            else if(letterGuess[0] == '#')
            {
                // Set letter guess to blank so we skip any letter checks
                letterGuess = "";

                // Prompt user to guess the word
                cout << "\nGuess the word: ";
                getline(cin, wordGuess);
            }

            // Player guess was valid and used up at least 1 guess
            validGuess = true;
            numOfGuesses++;
            
            // Guessed a letter
            if(letterGuess != "")
            {
                // Check player's guess - fill in corresponding letter locations
                bool letterFound = false;
                for(int i = 0; i < wordToGuess.length(); i++)
                {
                    if(tolower(letterGuess[0]) == tolower(wordToGuess[i]))
                    {
                        displayWord[i] = wordToGuess[i];
                        letterFound = true;
                    }
                }

                // If letter found let player know
                if(letterFound)
                {
                    cout << "\n";
                    cout << alienLeader.getName() << ": Correct. The word has the letter '" << letterGuess[0] << "' in it. " << endl; 
                }
                else 
                {  
                    cout << "\n";
                    cout << alienLeader.getName() << ": Incorrect. The word doesn't have the letter '" << letterGuess[0] << "' in it. " << endl; 
                }
            }
            // Guessed a word - only 1 chance
            else
            {
                // Check player's word guess 
                // Player WON by guessing right word
                if(wordGuess == wordToGuess)
                {
                    cout << "\n";
                    cout << "   [ WELL DONE! You've guessed the word '" << wordToGuess << "' in " << numOfGuesses << " guesses. ]" << endl;
                    delay();
                    // Respectful response
                    if(alienLeader.getImpression() > 150)
                    {
                        cout << alienLeader.getName() << ": Takes a lot of courage to guess the word outright." << endl;
                    }
                    // Non-respectful response
                    else
                    {
                        cout << alienLeader.getName() << ": Wow, straight to guessing the word huh? Showoff." << endl;  
                    }
                    delay();
                    // return true for 'win'
                    done = true;
                    wordFound = true;
                }
                // Player LOST by guessing wrong word
                else 
                {  
                    cout << "\n";
                    cout << "   [ You have failed to guess the word '" << wordToGuess << "'. You used " << numOfGuesses  << " guesses. ]" << endl;
                    delay();
                    // Respectful response
                    if(alienLeader.getImpression() > 150)
                    {
                        cout << alienLeader.getName() << ": I guess I should have picked an easier word." << endl;
                    }
                    // Non-respectful response
                    else
                    {
                        cout << alienLeader.getName() << ": Hahaha! I guess I overestimated your intelligence." << endl;  
                    }
                    delay();
                    // Player lost return false for 'win'
                    done = true;
                    wordFound = false;
                }
            }
            
            // Check if word found or guesses exhausted, otherwise continue guessing
            // Player WON by guessing letters
            if(displayWord == wordToGuess)
            {
                cout << "\n";
                cout << "   [ WELL DONE! You've guessed the word '" << wordToGuess << "' in " << numOfGuesses  << " guesses. ]" << endl;
                delay();
                // Respectful response
                if(alienLeader.getImpression() > 150)
                {
                    cout << alienLeader.getName() << ": Nice. You're smarter than I thought." << endl;
                }
                // Non-respectful response
                else
                {
                    cout << alienLeader.getName() << ": Humbug! You got lucky." << endl;  
                }
                delay();
                // return true for 'win'
                done = true;
                wordFound = true;
            }
            // Player LOST by guessing letters
            else if(numOfGuesses == MAX_GUESSES)
            {
                cout << "\n";
                cout << "   [ You have failed to guess the word '" << wordToGuess << "'. ]" << endl;
                delay();
                // Respectful response
                if(alienLeader.getImpression() > 150)
                {
                    cout << alienLeader.getName() << ": I guess I should have picked an easier word." << endl;
                }
                // Non-respectful response
                else
                {
                    cout << alienLeader.getName() << ": Hahaha! I guess I overestimated your intelligence." << endl;  
                }
                delay();
                // Player lost return false for 'win'
                done = true;
                wordFound = false;
            }
        }   
    }
    return wordFound;
}

/** Function simulates a dice gambling game 
 * @param Alien to use object methods
 * @param GameStats to use object methods
 * @return bool if player won or not.
*/
bool diceGame(Alien &alienLeader, GameStats &gameStats)
{
    // Display Instructions
    cout << "   [ The gambling table's holo-projector displays the following instructions... ] " << endl;
    delay();
    cout << "\n" << setfill('*') << setw(50) << "| DICE ROLL INSTRUCTIONS |" << setfill('*') << setw(20) << '*' << endl;
    cout << "\n1) Select your bet. (optional)" << endl;
    cout << "2) Roll 1 dice until you choose to stop or go past a sum of 15." << endl;
    cout << "3) There are only 5 rounds." << endl;
    cout << "4) Which ever player is closest to 15 WINS, except if one player goes over 15 - the one under 15 wins." << endl;
    cout << "5) Winner gets payed out double their bet." << endl;
    cout << "6) If there is a tie, house wins." << endl;
    cout << "\n" << setfill('*') << setw(70) << '*' << endl;
    delay();

    // Place bet
    cout << "   [ How much would you like to bet? (bet '0' to skip betting). ] " << endl;
    string bet = "";
    bool doneBetting = false;

    while(!doneBetting)
    {
        // Prompt user for bet
        int num = -1;
        bool done = false;
        while(!done) 
        {
            cout << "\nBet: $";
            getline(cin, bet);

            if(((int)bet[0] >= (int)'0' && (int)bet[0] <= (int)'9'))
            {
                done = true;
            }
            else
            {
                cout << "Invalid bet - please input an integer." << endl;
            }
        }
        cout << "\n";

        // Player chose 'no bet game' (playing for fun)
        if(stoi(bet) == 0)
        {
            cout << "   [ You have chosen a 'no bet' game. ]" << endl;
            doneBetting = true;
        }
        // Enough funds to secure a game
        else if(stoi(bet) <= gameStats.getMoney() && stoi(bet) > 0)
        {
            cout << "   [ You are betting: $" << bet <<". ]" << endl;
            gameStats.spendMoney(stoi(bet));
            doneBetting = true;
        }
        // Not enough funds - no bet game
        else if(gameStats.getMoney() < stoi(bet))
        {
            cout << "   [ Insufficient funds - current balance: $" << gameStats.getMoney() << " - resume 'no bet' game. ]" << endl;
            bet = "0";
            doneBetting = true;
        }
        else
        {
            cout << "   [ ** Please place a valid bet ** ]" << endl;
        }
        delay(); 
    }

    // Announce ready to play
    cout << "\n";
    cout << alienLeader.getName() << ": I am ready to throw some bones! You can roll first..." << endl;
    delay();

    // Dice Roll Loop
    int playerSum = 0;
    int alienSum = 0;
    bool playerDone = false;
    bool alienDone = false;
    const int MAX_ROUNDS = 5;
    int round = 1;
    
    // Loop stops when both player and alien are done OR after the final round
    while((!playerDone || !alienDone) && round <= MAX_ROUNDS)
    {
        cout << setfill(' ') << setw(10) << "\n\n ROUND " << round << ' ' <<  endl;
        cout << setfill('-') << setw(20) << '-' << endl;
        
        // If player not done, prompt player to roll dice or hold
        if(!playerDone)
        {
            cout << "\nWould you like to roll? ('no' to hold)." << endl;

            // Player chooses to roll
            if(choice() == "y")
            {
                cout << "\nYOUR ROLL:  " << endl;
                playerSum += diceRoll();
            }
            // Player chooses to hold
            else
            {
                playerDone = true;
            }
        }
        cout << "Ambassador " << gameStats.getPlayerName() << " Sum: " << playerSum << endl;

        // Gorlock will continue to roll up to a certain threshold
        if(alienSum < 13)
        {
            cout << "\nGORLOCK'S ROLL:  " << endl;
            alienSum += diceRoll();
            cout << alienLeader.getName() << " Sum: " << alienSum << endl;
        }
        // Gorlock stops rolling
        else
        {
            cout << "\n";
            cout << "   [ Gorlock is holding this round. ]" << endl;
            alienDone = true;
        }
        
        round++;
    }
    cout << "\n";

    // Game finished because both players 'hold'
    if(alienDone && playerDone)
    {
        cout << "   [ The game is done, both players are holding. ]" << endl;
        delay();
    }
    // Game finished because round limit reached
    else
    {
        cout << "   [ The final round is over! ]" << endl;
        delay();
    }
    cout << "   [ DICE SUM RESULTS | Ambassador: " << playerSum << " - Gorlock: " << alienSum << " ]" << endl;
    delay();
    

    // Determine if player won
    int win = false;

    // check for tie scenario
    if(playerSum == alienSum)
    {
        cout << "   [ TIE! House wins. ]" << endl;
        delay();
        cout << alienLeader.getName() << ": Darlop! I guess we're both losers." << endl;
    
        win = false;
    }
    // check if 1 person went over 15 and 1 stayed under 21
    else if(playerSum <= 15 && alienSum > 15 || playerSum > 15 && alienSum <= 15 )
    {
        // Player wins
        if(playerSum <= 15 && alienSum > 15)
        {
            cout << "   [ YOU WON! Your opponent went over 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": You got lucky is all." << endl;

            win = true;
        }
        // Alien wins
        else
        {
            cout << "   [ YOU LOST! You went over 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": Better luck next time." << endl;

            win = false;
        }
    }
    // both players over 15, so determine who is closest to 15.
    else if(playerSum > 15 && alienSum > 15)
    {
        // Player wins
        if(playerSum < alienSum)
        {
            cout << "   [ YOU WON! You were closer to 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": We both went over, but looks like you got luckier." << endl;

            win = true;
        }
        // Alien wins
        else
        {
            cout << "   [ YOU LOST! Gorlock was closer to 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": Close game! Maybe you'll do better next time." << endl;

            win = false;
        }
    }
    // both players under 15, so determine who is closest to 15.
    else
    {
        // Player wins
        if(playerSum > alienSum)
        {
            cout << "   [ YOU WON! You were closer to 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": Whatever. The table was uneven." << endl;
            win = true;
        }
        // Alien wins
        else
        {
            cout << "   [ YOU LOST! Gorlock was closer to 15. ]" << endl;
            delay();
            cout << alienLeader.getName() << ": HAHA! Luck is on my side!!!" << endl;
            win = false;
        }
    }
    delay();

    // Payout player if they won
    if(win)
    {
        // Win twice amount bet
        gameStats.addMoney(stod(bet) * 2.0);
        cout << "[ You won $" << fixed << setprecision(2) << stod(bet) << ". ]" << endl;
    }
    
    return win;
}

/** Function that simulates the roll of a 6-sided dice and prints dice out in ASCII art form
 * @return int roll result
*/
int diceRoll()
{
    // random number 1 - 6
    int rollResult = (rand() % 6) + 1; 
    
    cout << "\n";
    // Display roll
    switch(rollResult)
    {
        case 1:
        {
            cout << " ------- " << endl;
            cout << "|       |" << endl;
            cout << "|   O   |" << endl;
            cout << "|       |" << endl;
            cout << " ------- " << endl;
            break;
        }
        case 2:
        {
            cout << " ------- " << endl;
            cout << "| O     |" << endl;
            cout << "|       |" << endl;
            cout << "|     O |" << endl;
            cout << " ------- " << endl;
            break;
        }
        case 3:
        {
            cout << " ------- " << endl;
            cout << "| O     |" << endl;
            cout << "|   O   |" << endl;
            cout << "|     O |" << endl;
            cout << " ------- " << endl;
            break;
        }
        case 4:
        {
            cout << " ------- " << endl;
            cout << "| O   O |" << endl;
            cout << "|       |" << endl;
            cout << "| O   O |" << endl;
            cout << " ------- " << endl;
            break;
        }
        case 5:
        {
            cout << " ------- " << endl;
            cout << "| O   O |" << endl;
            cout << "|   O   |" << endl;
            cout << "| O   O |" << endl;
            cout << " ------- " << endl;
            break;
        }
        case 6:
        {
            cout << " ------- " << endl;
            cout << "| O   O |" << endl;
            cout << "| O   O |" << endl;
            cout << "| O   O |" << endl;
            cout << " ------- " << endl;
            break;
        }
    }
    cout << "\n";

    return rollResult; 
}

/** Function that simulates a robbery based off chance
 * @param Alien to use object methods
 * @param GameStats to use object methods
*/
void robberyEncounter(Alien &alienLeader, GameStats &gameStats)
{
    // Days spent in game
    int days = gameStats.getDays();
    
    // Check encounter chance (chance of being robbed decreases each day as people on board begin to see you spend more time with Gorlock)
    // formula adapted from Oregon Trail raiders encounter
    int encChance = (((((pow(((days)), 2) + 72) / ((pow(((days)), 2)) + 12)) - 1) / 0.10) / 2.0) + 0.5;
    
    // Random number 0 - 100
    int n = rand() % 100; 

    // Robbery Encounter happens if n <= encounter chance
    if(n <= encChance)
    {
        bool positiveInteraction = false;
        cout << "\n";
        cout << "     [ Out of nowhere you feel cold steel on the back of your neck and a voice whisper... ]" << endl;
        delay();
        cout << "     [ 'You're Gorlock's new pet aren't yah? - Well the big guy is too distracted by the smell of food right now, so why don't you fork over $10 and I won't 'fork' you up pal'. ]" << endl;
        delay();
        cout << "     [ Do you want to pay the $10? If not you will attempt to fight. ]" << endl;
        
        if(choice() == "n")
        {
            cout << "\n";
            cout << "     [ You refuse to pay and quickly turn to see a tall and lanky Forlatian thief. ]" << endl;
            delay();
            int winChance = ((rand() % 3 - 1 + 1) + 1); // range [1,3]..so a 2/3 chance of winning a fight - high risk, high reward
            // win 
            if(winChance != 3)
            {
                cout << "     [ Just as you throw a kick, you find youself falling to the ground ]" << endl;
                delay();
                cout << "     [ The thief is about to stab you. ]" << endl;
                delay();
                cout << "     [ You have a split second to counter - do you want to attempt to trip him? Otherwise you'll try to roll out of the way. ]" << endl;
                // Attempt headlock 
                if(choice() == "y")
                {                                                    
                    cout << "     [ You successfully trip the thief and hold him down. ]" << endl;
                    delay();
                    cout << "     [ Gorlock takes notice and calls the guards to have the thief thrown out an airlock. ]" << endl;
                    delay();
                    cout << alienLeader.getName() << ": Sorry I was distracted, but I am impressed to see you handle yourself." << endl;
                    delay();
                    positiveInteraction = true;
                    alienLeader.setImpression(alienLeader.getImpression() + 20);
                }
                // Protect head
                else
                {                                                    
                    cout << "     [ As the thief lifts his dagger to stab you, Gorlock fires his laser pistol into the theif's chest. He falls forward...hitting the ground. ]" << endl;
                    delay();
                    cout << alienLeader.getName() << ": Lucky I saw him in time, otherwise you might have been done for Ambassador." << endl;
                    delay();
                    positiveInteraction = true;
                    alienLeader.setImpression(alienLeader.getImpression() + 15);
                }
            }
            else
            {
                // Detail loss
                cout << "     [ The thief throws a couple of daggers at you - hitting you in the chest, arms, and kidneys. At the sight of blood, the thief flees. ]" << endl;
                delay();
                cout << "     [ You're in critical condition and will need to be flown to a nearby UNE medical station. ]" << endl;
                delay();
                cout << alienLeader.getName() << ": Oh my! Looks like a Forlatian thief got you. You best get off the station and get to a medical facility." << endl;
                delay();
                positiveInteraction = false;
                alienLeader.setImpression(alienLeader.getImpression() - 40);
                
                // End game - lose scenario
                gameStats.setWin(false);
                gameStats.setGameOver(true);

            }
            gameStats.passTime(alienLeader, 2);
        }
        // Pay the $10
        else
        {
            // Attempt to pay $10
            cout << "\n";
            cout << "     [ You decide to hand over $10... ]" << endl;
            delay();

            // Check if player has enough funds
            if(gameStats.getMoney() >= 10)
            {
                gameStats.spendMoney(10);
                cout << "     [ The thief grabs the cash and dissapears into the Mess Hall crowd. ]" << endl;
            }
            // Not enough funds
            else
            {
                // Detail loss
                cout << "     [ The thief shouts 'An Ambassador without $10 to spare?! Pathetic!' then proceeds to stab you. ]" << endl;
                delay();
                cout << "     [ You're in critical condition and will need to be flown to a nearby UNE medical station. ]" << endl;
                delay();
                cout << alienLeader.getName() << ": Oh my! Looks like a Forlatian thief got you. You best get off the station an get to a medical facility." << endl;
                delay();
                positiveInteraction = false;
                alienLeader.setImpression(alienLeader.getImpression() - 40);
                
                // End game - lose scenario
                gameStats.setWin(false);
                gameStats.setGameOver(true);
            }
            delay();
            cout << alienLeader.getName() << ": ...always keep some money on hand, these Forlatian theives are always hanging around the Mess Hall." << endl;
            delay();
            gameStats.passTime(alienLeader, 1);
        }
        gameStats.interactionCount(positiveInteraction);
    }
}


// ** ORGANIZATIONAL ** 
/** Function details optional intro - has game back story and lead-up dialogue. 
 * @param Alien object to use stats
 * @param GameStats object use stats
 */
void gameIntro(Alien &alienLeader, GameStats &gameStats)
{
    // Preamble
    cout << "     [ An urgent letter arrives for Ambassador " << gameStats.getPlayerName() << " - you open it.]" << endl;
    delay();
    
    // Letter
    cout << "Dear " << gameStats.getPlayerName() << ", " << endl;
    cout << "\n     It's 2420 and as you know, Earth continues to be at war with the inhabitants of Sumac9. A large and harsh planet ravaged by storms and monstrous creatures. The humanoid inhabitants match the ferocity of the planet, but are not wholly unreasonable.";
    cout << " The war has gone on for over a century and both sides have seen more bloodshed than anyone expected. Still, the Sumacians show no sign of being the first to broker a peace treaty - it’s a matter of honor than practicality.";
    cout << " The UNE or United Nations of Earth have tasked you to visit the homebase of the Sumacian leader, " << alienLeader.getName() << ", a hospitable yet temperamental being with plenty of power and influence.";
    cout << " Though he doesn’t make it public, the UNE suspects he has become fond of humans. They believe the time is ripe for proposing a peace treaty and that you’ll be the one to deliver the proposal.";
    cout << " You have your work cut out for you. You only have " << gameStats.getMaxDays() << " days until the Sumacians unleash their M.E.G.G.U.H. Cannon...at that point any hope for peace would be squashed.";
    cout << " During that time you are to earn " << alienLeader.getName() << "'s trust, so timing is key when offering the proposal. The UNE believes you are the best they got, so don’t mess this up!" << endl;
    cout << "\nBest," << endl;
    cout << "--UNE Council" << endl;
    cout << "P.S. We have a ship at the dock ready to take you to Sumac9 ASAP." << endl;
    
    // Departure
    delay();
    cout << "     [ You take off with no time to waste. ]" << endl;
    delay();
    cout << "     [ It's been 42 days, but Sumac9's glowing blue moon is finally in sight. ]" << endl;
    delay();
    
    // Arrival
    cout << "     [ Your ship arrives at Sumac9's docking bay and a bunch of small Sumacian grunts run over and grab your bags. ]" << endl;
    delay();
    cout << "     [ At the docking bay a large man-like creature adorned with a necklace of human skulls and a cyber machete at his waist approaches you with some familiarity... ]" << endl;
    delay();
    cout << "Man-Like Creature: *HEAD BUTT*. HAHAHA! I am " << alienLeader.getName() << "! " << "MANY WELCOMES AMBASSADOR! It's ambassador " << gameStats.getPlayerName() << " right?! Oh no matter, please come inside our headquarters. I look forward to your company for the next " << gameStats.getMaxDays() << " days." << endl;
    delay();
    cout << "     [ You follow Gorlock into the headquarters...and so your mission begins. Remember, earn Gorlock's trust for at least the first 3 days before presenting the peace treaty. ]" << endl;
}

/** Function details outro - lets player know if they won or loss
 * @param Alien object to use stats
 * @param GameStats object use stats
 */
void gameOutro(Alien alienLeader, GameStats gameStats)
{
    // Delineate end of game from rest of game
    cout << "\n";
    cout << setfill('*') << setw(80) << '*' << endl;
    cout << "\n\n";
    cout << "     [ Your ship successful leaves Sumac9's docking bay. ]" << endl;
    delay();
    cout << "     [ You look out the ships rear and see a giant explosion... ]" << endl;
    delay();

    // Win outro
    if(gameStats.getWin())
    {   
        // Preamble
        cout << "     [ Your heart sings as you see the dismantling of the M.E.G.G.U.H. Cannon!!! You're filled with a sense of relief... ]" << endl;
        delay();
        cout << "     [ A message from the UNE council comes in. ]" << endl;
        delay();
        
        // Letter
        cout << "\nDear " << gameStats.getPlayerName() << ", " << endl;
        cout << "\n     We are pleased to announce that the Earth & Sumac9 peace treaty has been finalized. Thanks to your SUCCESS, the war is finally over. Your diplomacy skills prevented more bloodshed!";
        cout << " WELL DONE! We look forward to your return...a celebration is in order!" << endl;
        cout << "\nVery Best," << endl;
        cout << "--UNE Council" << endl;
        
        // Arrival
        cout << "\n";
        cout << "     [ Your ship arrives at the UNE headquarters and you are greeted by cheers and festivities! ]" << endl;
        delay();

        cout << "                           *    *                                          " << endl;
        cout << "*         '       *       .  *   '     .           * *                     " << endl;
        cout << "                                                            '              " << endl;
        cout << "    *                *'          *          *        '                     " << endl;
        cout << ".           *               |               /                              " << endl;
        cout << "            '.         |    |      '       |   '     *                     " << endl;
        cout << "                \\*        \\   \\             /                           " << endl;
        cout << "    '            \\     '* |    |  *        |*                *  *         " << endl;
        cout << "            *      `.       \\   |     *     /    *      '                 " << endl;
        cout << ".                  \\      |   \\          /               *               " << endl;
        cout << "    *'  *     '      \\      \\   '.       |                               " << endl;
        cout << "        -._            `                  /         *                      " << endl;
        cout << "' '      ``._   *                           '          .      '            " << endl;
        cout << "*           *\\*          * .   .      *                                   " << endl;
        cout << setfill(' ') << setw(40) << "T H A N K  Y O U" << setfill(' ') << setw(10) << ' ' << endl;
        cout << "            .  '      *       *    *   .       _ *   .                     " << endl;
        cout << setfill(' ') << setw(40) << "AMBASSADOR " << gameStats.getPlayerName() << setfill(' ') << setw(10) << ' ' << endl;
        cout << ".               '             . '   *           *         .                " << endl;
        cout << "*       ___.-=--..-._     *                '               '               " << endl;
        cout << "                                *       *                                  " << endl;
        cout << "                *        _.'  .'       `.        '  *             *        " << endl;
        cout << "    *              *_.-'   .'            `.               *                " << endl;
        cout << "                .'                       `._             *  '              " << endl;
        cout << "'       '                        .       .  `.     .                       " << endl;
        cout << "    .                      *                  `                            " << endl;
        cout << "            *        '             '                          .            " << endl;
        cout << "    .                          *        .           *  *                   " << endl;         
        cout << "            *        .                                    '                " << endl;
        delay();
        cout << "       [ YOU'VE WON! WELL DONE! ]" << endl;
    }
    // Lost outro
    else
    {
        // Preamble
        cout << "     [ Your heart sinks as you hear the firing of the M.E.G.G.U.H. Cannon. You're filled with a sense of dread...]" << endl;
        delay();
        cout << "     [ A message from the UNE council comes in. ]" << endl;
        delay();
        
        // Letter
        cout << "Dear " << gameStats.getPlayerName() << ", " << endl;
        cout << "\n     The M.E.G.G.U.H. cannon has been fired...too many will die now. Your diplomacy skills have FAILED us. This war may never end..." << endl;
        cout << "\nWorst," << endl;
        cout << "--UNE Council" << endl;
        delay();
        cout << "     [ YOU'VE LOST. Better luck next time. ]" << endl;
    }
    delay();
}

void gameInstructions()
{
    cout << "\n";
    cout << setfill('*') << setw(40) << "| HOW TO PLAY |" << setw(40) << '*' << endl;
    
    cout << "\n";
    cout << "OVERVIEW:" << endl;
    cout << "> You play the role of an Ambassador here to make peace with the alien leader Gorlock. You'll spend several days learning his preferences, playing games, chatting, etc..." << endl;
    cout << "> The more you please him the more likely he will be willing to sign a peace deal." << endl;
    
    cout << "\n";
    cout << "WIN CONDITIONS: " << endl;
    cout << "> You must meet the following 4 conditions THEN offer the peace treatise: " << endl;
    cout << "   1. Be at the base for at least 3 days." << endl;
    cout << "   2. Gorlock needs to be in a good mood - you'll learn that by talking or listening to him." << endl;
    cout << "   3. Gorlock needs to be somewhat impressed by you - again, talk and listen to him to find out." << endl;
    cout << "   4. Have more positive(+) interactions than negative(-) interactions - check your log to see where you stand." << endl;
   
    cout << "\n";
    cout << "TIME: " << endl;
    cout << "> Time on Sumac9 works a bit differently. There are 10.0 Earth hours in a Sumacian day." << endl;
    cout << "> Almost every activity takes up some time, so pick each activity per day wisely!" << endl;
    cout << "> Different parts of the game and reactions occur depending on the time of day, so try things out at different hours." << endl;
    cout << "> There are between 5-10 days you have before the game ends, the number of days depends on the difficulty you choose." << endl;
    cout << "> Watch the clock, if you don't rest before the 10th hour you will not be as well rested and will upset Gorlock." << endl;

    cout << "\n";
    cout << "MONEY: "  << endl;
    cout << "> You're given a small sum in the beginning of the game and you'll have money deposited into your account every time you start a new day." << endl;
    cout << "> You can earn more money by gambling...but also lose it." << endl;
    cout << "> Money is used to buy food, pay off thieves, pay hackers, and gamble. Money is also calculated into your score." << endl;

    cout << "\n";
    cout << "SCORE: " << endl;
    cout << "> Scores are strictly a vanity thing and help you compare yourself to others who've played or your previous games. It does not effect end game results." << endl;
    cout << "> The DAILY SCORE is in flux throughout the day, it goes up during positive events or play and down during negative events." << endl;
    cout << "> The DAILY SCORE is added to the FINAL SCORE at the end of each day. Also note that the DAILY SCORE doesn't zero out during a new day, it rolls over. Use this to strategize between rest and optimal points in a day." << endl;
    cout << "> The FINAL SCORE is just the sum of daily scores and bonus points from winning the game. The higher the difficulty the more BONUS points you earn." << endl;
    
    cout << "\n";
    cout << "TIPS: " << endl;
    cout << "> Alien Ambassador is part luck, but mostly play style. You're essentially baby sitting a big alien, so keep him fed, entertained, rested, and impressed." << endl;
    cout << "> Talking to Gorlock will give you a chance to get positive interactions without much risk, but won't do too much for his mood - so make sure you play with him or eat with him in between talks." << endl;
    cout << "> The first interaction of the day should be an ice breaker - but you're free to do what you will." << endl;
    cout << "> REST when Gorlock gets tired or when it gets late. There are consequences to falling asleep on the ground." << endl;
    cout << "> Check your computer log and pay hackers to get a better idea of where you stand with Gorlock." << endl;
    cout << "> Note which activities take longer than others - order your day accordingly." << endl;
    cout << "\n";
    cout << setfill('*') << setw(80) << '*' << endl;
}