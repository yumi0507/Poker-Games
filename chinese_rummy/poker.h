#ifndef POKER_H
#define POKER_H
#include <vector>
#include <string>
using namespace std;

class poker{
    int num;
    int shape;
    vector<string> card;

public:
    poker(int, int);
    int getNum();
    int getShape();
    vector<string> getCard();
    
};

class deck{
    vector<poker> poker_card;

public:
    deck();
    vector<poker> getPoker();
    void showCard(int);
    void showCard(poker);
    void showCard(vector<poker>, int);
    void shuffleCard();
    void shuffleCard(vector<poker>&);
    poker dealCard();
    void returnCard(poker);
    void resetDeck();

};

#endif