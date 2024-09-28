#ifndef NINETY_NINE_H
#define NINETY_NINE_H

#include <string>
#include <vector>
#include "poker.h"

class player{
    string name;
    int point;
    vector<poker> hand;

public:
    player(string);
    string getName();
    void inHand(poker);
    void outHand(int);
    void eraseHand();
    vector<poker> getHand();
    void setPoint(int);
    int getPoint();
};

class rule{
    int sum;
    bool fourPlayer;
    vector<player> players;
    vector<int> order;
    deck aDeck;
    int turn;
    bool forward;
    int loser;

public:
    rule();
    void addPlayer(int);
    int getOrder();
    void startGame();
    void play();
    void setSum(int);
    void checkForward();
    void checkTurn();
    void exitGame();
    void lose();
    void win();
    void getPoint();
    void rank();

};

#endif