#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <windows.h>
#include "poker.h"
using namespace std;

void SetColor(int color = 7)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}

vector<string> top{
    "*********************",
};

vector<vector<string>> number{
    {
        "*  A                *",
        "*                A  *",
    },

    {
        "*  2                *",
        "*                2  *",
    },

    {
        "*  3                *",
        "*                3  *",
    },

    {
        "*  4                *",
        "*                4  *",
    },

    {
        "*  5                *",
        "*                5  *",
    },

    {
        "*  6                *",
        "*                6  *",
    },

    {
        "*  7                *",
        "*                7  *",
    },

    {
        "*  8                *",
        "*                8  *",
    },

    {
        "*  9                *",
        "*                9  *",
    },

    {
        "* 1 0               *",
        "*               1 0 *",
    },

    {
        "*  J                *",
        "*                J  *",
    },

    {
        "*  Q                *",
        "*                Q  *",
    },

    {
        "*  K                *",
        "*                K  *",
    },
};


vector<vector<string>> suit{
    {
        "*        +++        *",
        "*     cl *v* ub     *",
        "*    +++--+--+++    *",
        "*     ++  +  ++     *",
        "*        /|\\        *",
        "*       +++++       *",
    },

    {
        "*         +         *",
        "*       +++++       *",
        "*     +++>W<+++     *",
        "*      diamond      *",
        "*       +++++       *",
        "*         +         *",
    },

    {
        "*       _   _       *",
        "*     +++. .+++     *",
        "*    +++++v+++++    *",
        "*     +++++++++     *",
        "*       heart       *",
        "*         +         *",
    },

    {
        "*         ^         *",
        "*       spade       *",
        "*      ++^U^++      *",
        "*     +++ | +++     *",
        "*         +         *",
        "*      +++++++      *",
    },
};


// poker part
poker::poker(int n, int s){
    num = n;
    shape = s;

    card.push_back(top[0]);
    card.push_back(number[num-1][0]);

    for(int i = 0; i < 6; i++)
        card.push_back(suit[shape-1][i]);
    
    card.push_back(number[num-1][1]);
    card.push_back(top[0]);

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
        for(int row = 0; row < 10; row++){
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
    
    for(int row = 0; row < 10; row++){
        if(Card.getShape() == 1 || Card.getShape() == 4)
            SetColor(112);
        else if(Card.getShape() == 2 || Card.getShape() == 3)
            SetColor(124);
        cout << Card.getCard()[row];
        SetColor();
        cout << endl;
    }
    SetColor();
}

void deck::showCard(vector<poker> Cards, int n){
    int i = 0;
    for(; i < Cards.size(); i += n){
        for(int row = 0; row < 10; row++){
            int temp = i;
            for(int times = 0; times < n; times++){
                vector<string> aCard = Cards[temp].getCard();
                if(Cards[temp].getShape() == 1 || Cards[temp].getShape() == 4)
                    SetColor(112);
                else if(Cards[temp].getShape() == 2 || Cards[temp].getShape() == 3)
                    SetColor(124);
                cout << aCard[row];
                SetColor();
                cout << "  ";
                if(temp == Cards.size()-1)
                    break;
                temp++;
            }cout << endl;
        }

        for(int times = 1; times <= n; times++){
            cout << "         ";
            if(i+times < 10)
                cout << " ";
            cout << i+times << "          " << "  ";
            if(i+times == Cards.size())
                break;
        }cout << endl;
    }cout << endl;
}

void deck::shuffleCard(){
    srand(time(NULL));
    int n = poker_card.size();
    int t = 3;
    while(t--){
        for(int i = 0; i < n; i++){
            int r = rand() % n;
            while(r == i)
                r = rand() % n;
            swap(poker_card[i], poker_card[r]);
        }
    }
}

void deck::shuffleCard(vector<poker>& Cards){
    srand(time(NULL));
    int n = Cards.size();
    int t = 3;
    while(t--){
        for(int i = 0; i < n; i++){
            int r = rand() % n;
            while(r == i)
                r = rand() % n;
            swap(poker_card[i], poker_card[r]);
        }
    }
}

poker deck::dealCard(){
    shuffleCard();
    poker deal = poker_card[poker_card.size()-1];
    poker_card.pop_back();
    return deal;
}

void deck::returnCard(poker get){
    poker_card.push_back(get);
    shuffleCard();
}

void deck::resetDeck(){
    poker_card.clear();
    for(int i = 1; i < 14; i++){
        for(int j = 1; j < 5; j++){
            poker_card.push_back(poker(i, j));
        }
    }
}