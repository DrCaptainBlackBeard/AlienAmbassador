// Talk Implementation
#include "Talk.h"
#include <iostream>
#include <string>
using namespace std;

// Default constructor
Talk::Talk()
{
    topic = "";
    playerSays = "";
    posResponse = "";
    negResponse = "";
}
// Parametrized constructor
Talk::Talk(string new_topic, string new_playerSays, string new_posResponse, string new_negResponse)
{
    topic = new_topic;
    playerSays = new_playerSays;
    posResponse = new_posResponse;
    negResponse = new_negResponse;
}

// Setters
void Talk::setTopic(string new_topic)
{
    topic = new_topic;
}
void Talk::setPlayerSays(string new_playerSays)
{
    playerSays = new_playerSays;
}
void Talk::setPosResponse(string new_posResponse)
{
    posResponse = new_posResponse;
}
void Talk::setNegResponse(string new_negResponse)
{
    negResponse = new_negResponse;
}

// Getters
string Talk::getTopic() const
{
    return topic;
}
string Talk::getPlayerSays() const
{
    return playerSays;
}
string Talk::getPosResponse() const
{
    return posResponse;
}
string Talk::getNegResponse() const
{
    return negResponse;
}