// Talk Header File

#ifndef TALK_H
#define TALK_H
#include <iostream>
#include <string>
using namespace std;

class Talk
{
// Member functions
public:
    // Default constructor
    Talk();
    // Parametrized constructor
    Talk(string new_topic, string new_playerSays, string new_posResponse, string new_negResponse);

    // Setters
    void setTopic(string new_topic);
    void setPlayerSays(string new_playerSays);
    void setPosResponse(string new_posResponse);
    void setNegResponse(string new_negResponse);

    // Getters
    string getTopic() const;
    string getPlayerSays() const;
    string getPosResponse() const;
    string getNegResponse() const;

// Data members
private:
    string topic;
    string playerSays;
    string posResponse;
    string negResponse;
};
#endif