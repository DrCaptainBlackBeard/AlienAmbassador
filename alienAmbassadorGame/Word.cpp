// Word driver file
#include "Word.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
    
    
// Constructors
// Default
Word::Word()
{
    word = "";
    clue = "";
}
// Parameterized constructor
Word::Word(string new_word, string new_clue)
{
    word = new_word;
    clue = new_clue;
}

// Setters
void Word::setWord(string new_word)
{
    word = new_word;
}
void Word::setClue(string new_clue)
{
    clue = new_clue;
}

// Getters
string Word::getWord() const
{
    return word;
}
string Word::getClue() const
{
    return clue;
}