#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include "poker.h"
using namespace std;

vector<string> top{
    "*****************************",
    "*                           *",
};

vector<string> bottom{
    "*                           *",
    "*****************************",
};


vector<vector<string>> number{
    {
        "*       A                   *",
        "*      A A                  *",
        "*     A   A                 *",
        "*     AAAAA                 *",
        "*     A   A                 *",
    },

    {
        "*     22222                 *",
        "*         2                 *",
        "*     22222                 *",
        "*     2                     *",
        "*     22222                 *",
    },

    {
        "*     33333                 *",
        "*         3                 *",
        "*     33333                 *",
        "*         3                 *",
        "*     33333                 *",
    },

    {
        "*     4   4                 *",
        "*     4   4                 *",
        "*     44444                 *",
        "*         4                 *",
        "*         4                 *",
    },

    {
        "*     55555                 *",
        "*     5                     *",
        "*     55555                 *",
        "*         5                 *",
        "*     55555                 *",
    },

    {
        "*     66666                 *",
        "*     6                     *",
        "*     66666                 *",
        "*     6   6                 *",
        "*     66666                 *",
    },

    {
        "*     77777                 *",
        "*         7                 *",
        "*         7                 *",
        "*         7                 *",
        "*         7                 *",
    },

    {
        "*     88888                 *",
        "*     8   8                 *",
        "*     88888                 *",
        "*     8   8                 *",
        "*     88888                 *",
    },

    {
        "*     99999                 *",
        "*     9   9                 *",
        "*     99999                 *",
        "*         9                 *",
        "*     99999                 *",
    },

    {
        "*   1   00000               *",
        "*   1   0   0               *",
        "*   1   0   0               *",
        "*   1   0   0               *",
        "*   1   00000               *",
    },

    {
        "*     JJJJJ                 *",
        "*        J                  *",
        "*        J                  *",
        "*     J  J                  *",
        "*     JJJJ                  *",
    },

    {
        "*     QQQQQ                 *",
        "*     Q   Q                 *",
        "*     Q Q Q                 *",
        "*     Q  QQ                 *",
        "*     QQQQQ                 *",
    },

    {
        "*     K   K                 *",
        "*     K  K                  *",
        "*     KK                    *",
        "*     K  K                  *",
        "*     K    K                *",
    },
};


vector<vector<string>> suit{
    {
        "*              +++          *",
        "*             +o3o+         *",
        "*         +++  +++  +++     *",
        "*        +++++--+--+++++    *",
        "*         +++   +   +++     *",
        "*              +++          *",
        "*            +++++++        *",
    },

    {
        "*               +           *",
        "*             +++++         *",
        "*           +++++++++       *",
        "*          ++++>w<++++      *",
        "*           +++++++++       *",
        "*             +++++         *",
        "*               +           *",
    },

    {
        "*                           *",
        "*          ++++. .++++      *",
        "*         ++++++v++++++     *",
        "*          +++++++++++      *",
        "*           +++++++++       *",
        "*             +++++         *",
        "*               +           *",
    },

    {
        "*               +           *",
        "*             +++++         *",
        "*           +++^U^+++       *",
        "*          +++++++++++      *",
        "*          +++  +  +++      *",
        "*              +++          *",
        "*            +++++++        *",
    },
};


// poker part
poker::poker(int n, int s){
    num = n;
    shape = s;

    for(auto i : top)
        card.push_back(i);

    for(int i = 0; i < 5; i++)
        card.push_back(number[num-1][i]);

    for(int i = 0; i < 7; i++)
        card.push_back(suit[shape-1][i]);

    for(auto i : bottom)
        card.push_back(i);

}

int poker::getNum(){
    return num;
}

int poker::getShape(){
    return shape;
}

vector<string> poker::getCard(){
    return card;
}


// deck part
deck::deck(){
    for(int i = 1; i < 14; i++){
        for(int j = 1; j < 5; j++){
            poker_card.push_back(poker(i, j));
        }
    }
}

vector<poker> deck::getPoker(){
    return poker_card;
}

void deck::showCard(int n){
    int i = 0;
    for(; i < poker_card.size(); i += n){
        for(int row = 0; row < 16; row++){
            int temp = i;
            for(int times = 0; times < n; times++){
                vector<string> aCard = poker_card[temp].getCard();
                cout << aCard[row] << " ";
                if(temp == 51)
                    break;
                temp++;
            }cout << endl;
        }
    }
}

void deck::showCard(poker Card){
    for(int row = 0; row < 16; row++){
        cout << Card.getCard()[row] << endl;
    }
}

void deck::showCard(vector<poker> Cards, int n){
    int i = 0;
    for(; i < Cards.size(); i += n){
        for(int row = 0; row < 16; row++){
            int temp = i;
            for(int times = 0; times < n; times++){
                vector<string> aCard = Cards[temp].getCard();
                cout << aCard[row] << " ";
                if(temp == 51)
                    break;
                temp++;
            }cout << endl;
        }
    }
}

void deck::shuffleCard(){
    srand(time(NULL));
    int n = poker_card.size();
    for(int i = 0; i < n; i++){
        int r = rand() % n;
        while(r == i)
            r = rand() % n;
        swap(poker_card[i], poker_card[r]);
    }
}

void deck::shuffleCard(vector<poker>* Cards){
    srand(time(NULL));
    int t = rand() % 500;
    int n = Cards->size();
    while(t--){
        int a = rand() % n;
        int b = rand() % n;
        swap((*Cards)[a], (*Cards)[b]);
    }
}

poker deck::dealCard(){
    shuffleCard();
    poker deal = poker_card[poker_card.size()-1];
    poker_card.pop_back();
    return deal;
}

poker deck::dealCard(vector<poker>* Cards){
    shuffleCard(Cards);
    poker deal = (*Cards)[Cards->size()-1];
    Cards->pop_back();
    return deal;
}

void deck::returnCard(poker get){
    poker_card.push_back(get);
    shuffleCard();
}

void deck::returnCard(vector<poker>* Cards, poker get){
    (*Cards).push_back(get);
}