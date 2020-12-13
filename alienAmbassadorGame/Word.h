// Word Header File
#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Word
{
// Member functions
public:
    // Constructors
    Word();
    Word(string new_word, string new_clue);

    // Setters
    void setWord(string new_word);
    void setClue(string new_clue);

    // Getters
    string getWord() const;
    string getClue() const;
    
// Data members
private:
    string word;
    string clue;
};
#endif