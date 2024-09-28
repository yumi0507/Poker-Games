#ifndef CHINESE_RUMMY_H
#define CHINESE_RUMMY_H

#include <string>
#include <vector>
#include "poker.h"
using namespace std;

class player{
private:
    string name;
    int point;
    vector<poker> hand;

public:
    player(string);
    string getName();
    int handSize();
    void inHand(poker);
    poker outHand(int);
    void eraseHand();
    vector<poker> getHand();
    void setPoint(int);
    void resetPoint();
    int getPoint();
};

class rule{
private:
    deck aDeck;
    int turn;
    vector<player> players;
    vector<poker> onDesk;
    bool end;

public:
    rule();
    void addPlayer(int);    // done
    void startGame();
    void play();
    void pick_up();
    void give_up();
    void outDesk(int);
    void rank();
    int input(string, int, int = 0);
    bool End();

};

class Operator{
private:
    poker card;

public:
    Operator(poker);
    int operator+(Operator&);
    int getNum();
    int getShape();

};

#endif