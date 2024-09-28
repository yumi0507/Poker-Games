#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "poker.h"
#include "chinese_rummy.h"
using namespace std;

// player part
player::player(string str){
    name = str;
    point = 0;
}

string player::getName(){
    return name;
}

int player::handSize(){
    return hand.size();
}

void player::inHand(poker get){
    hand.push_back(get);
}

poker player::outHand(int n){
    poker out = hand[n];
    hand.erase(hand.begin()+n);
    return out;
}

void player::eraseHand(){
    hand.clear();
}

vector<poker> player::getHand(){
    return hand;
}

void player::setPoint(int p){
    point += p;
}

void player::resetPoint(){
    point = 0;
}

int player::getPoint(){
    return point;
}


// rule part
rule::rule(){
    turn = 0;
    end = false;
}

void rule::addPlayer(int num){
    for(int i = 0; i < num; i++){
        string str;
        cout << "Enter you name (in English): ";
        cin >> str;
        player p(str);
        players.push_back(p);
        if(i == num-1){
            cin.get();
            cout << "------------------------------" << endl << endl;
        }else
            cout << "Next player ->" << endl;
    }

}

void rule::startGame(){
    end = false;
    aDeck.resetDeck();
    onDesk.clear();
    cout << "Ordering..." << endl << endl;
    aDeck.shuffleCard();
    
    for(int i = 0; i < players.size(); i++){
        players[i].resetPoint();
        players[i].eraseHand();
        players[i].inHand(aDeck.dealCard());
        for(int j = 0; j < i; j++){
            if(players[i].getHand()[0].getNum() > players[j].getHand()[0].getNum())
                swap(players[i], players[j]);
            else if(players[i].getHand()[0].getNum() == players[j].getHand()[0].getNum())
                if(players[i].getHand()[0].getShape() > players[j].getHand()[0].getShape())
                    swap(players[i], players[j]);
        }
    }

    for(int i = 0; i < 24; i++){
        onDesk.push_back(aDeck.dealCard());
    }aDeck.shuffleCard(onDesk);

    for(auto &i : players){
        cout << i.getName() << ": " << endl;
        aDeck.showCard(i.getHand()[0]);
        cout << endl;
        aDeck.returnCard(i.outHand(0));
        for(int j = 0; j < 24 / players.size(); j++){
            i.inHand(onDesk[onDesk.size()-1]);
            onDesk.pop_back();
        }
    }

    int t = 4;
    while(t--){
        onDesk.push_back(aDeck.dealCard());
    }

    cout << "Press Blank Space to start the game." << endl;
    while(true){
        if(getch() == ' '){
            system("cls");
            break;
        }
    }
}

void rule::play(){    
    cout << "It's " << players[turn].getName() << "'s turn. ";
    cout << "(";
    for(int i = 0; i < players.size(); i++){
        cout << players[i].getName() << ": " << players[i].getPoint() << " points";
        if(i == players.size()-1)
            cout << ")" << endl;
        else
            cout << ", ";
    }
    cout << "Cards on the desk:" << endl;
    aDeck.showCard(onDesk, 4);
    cout << endl;
    cout << "Your hand:" << endl;
    aDeck.showCard(players[turn].getHand(), 4);
    char func = 'a';
    cout << "1. Pick up a card" << endl;
    cout << "2. Give up a card" << endl;
    while(func != '1' && func != '2'){
        cout << "Choose the number: ";
        cin >> func;
        cout << endl;
        if(func == '1' || func == '2')
            break;
        cout << "Input error. Please re-enter your choice." << endl;        
    }system("cls");


    if(func == '1'){
        pick_up();
    }else if(func == '2'){
        give_up();
    }

    cout << "Player " << players[turn].getName() << "'s points: " << players[turn].getPoint() << " point";
    if(players[turn].getPoint() > 1)
        cout << "s";
    cout << "." << endl;
    cout << "Press Blank Space to continue." << endl;
    while(true){
        if(getch() == ' '){
            system("cls");
            break;
        }
    }
    turn++;
    if(turn == players.size())
        turn = 0;
}

void rule::pick_up(){
    int n = input("from your hand", players[turn].handSize());
    int m = input("on the desk", onDesk.size(), n);
    poker Hand = players[turn].getHand()[n];
    poker Desk = onDesk[m];
    while(Hand.getNum()+Desk.getNum() != 10){
        if(Hand.getNum() == Desk.getNum() && Hand.getNum() >= 10)
            break;
        system("cls");
        cout << players[turn].getName() << ", please choose your cards again or enter 'g' to give up a card" << endl;
        n = input("from your hand", players[turn].handSize(),-2);
        if(n == -2){
            give_up();
            return;
        }
        Hand = players[turn].getHand()[n];
        m = input("on the desk", onDesk.size(), n);
        Desk = onDesk[m];
    }
    Operator handout(Hand);
    Operator deskout(Desk);

    cout << "Player " << players[turn].getName() << " gets " << handout+deskout << " point";
    if(handout+deskout > 1)
        cout << "s";
    cout << "." << endl;
    players[turn].setPoint(handout+deskout);
    players[turn].outHand(n);
    outDesk(m);

}

void rule::give_up(){    
    int n = input("from your hand", players[turn].handSize(), -1);
    onDesk.push_back(players[turn].outHand(n));
}

void rule::outDesk(int n){
    onDesk.erase(onDesk.begin()+n);
    if(aDeck.getPoker().size() > 0)
        onDesk.push_back(aDeck.dealCard());
}

void rule::rank(){
    cout << "The end of game." << endl;
    cout << "------------------------------" << endl << endl;

    for(int i = 0; i < players.size()-1; i++){
        for(int j = i+1; j < players.size(); j++){
            if(players[i].getPoint() < players[j].getPoint())
                swap(players[i], players[j]);
        }
    }

    cout << endl << "Ranking:";
    int ranking = 0;
    for(int i = 0; i < players.size(); i++){
        if(i == 0 || players[i].getPoint() != players[i-1].getPoint()){
            cout << endl;
            cout << "No." << ++ranking << " (" << players[i].getPoint();
            if(players[i].getPoint() <= 1)
                cout << " point ";
            else
                cout << " points";             
            cout << "): ";    
        }cout << players[i].getName() << " ";
    }
    cout << endl << "------------------------------" << endl << endl;
}

int rule::input(string str, int range, int card){
    if(str == "from your hand"){
        if(card != -2){
            cout << "~" << players[turn].getName() << "'s Round~" << endl;
        }
        if(card != -1){
            cout << "Cards on the desk:" << endl;
            aDeck.showCard(onDesk, 4);
            cout << endl;
        }
        cout << "Your hand:" << endl;
        aDeck.showCard(players[turn].getHand(), 4);
    }else if(str == "on the desk"){
        system("cls");
        cout << "~" << players[turn].getName() << "'s Round~" << endl << endl;
        cout << "You chose from your hand:" << endl;
        aDeck.showCard(players[turn].getHand()[card]);
        cout << endl;
        cout << "Cards on the desk:" << endl;
        aDeck.showCard(onDesk, 4);
    }

    cout << "Choose a card " << str << "(1~" << range << ")";
    if(card == -2)
        cout << " or 'g' to give up a card";
    cout << ": ";
    int n = -1;
    while(true){
        string temp;
        cin >> temp;

        if(card == -2 && temp.size() == 1 && temp[0] == 'g'){
            n = -2;
        }

        if(range >= 10){
            char tens = char(range/10 + '0');
            char units = char(range%10 + '0');
            if(temp.size() == 2){
                if(temp[0] >= '1' && temp[0] < tens){
                    if(temp[1] >= '0' && temp[1] <= '9'){
                        n = int(temp[0]-'0') * 10 + int(temp[1]-'1');
                    }
                }else if(temp[0] == tens){
                    if(temp[1] >= '0' && temp[1] <= units){
                        n = int(temp[0]-'0') * 10 + int(temp[1]-'1');
                    }         
                }
            }else if(temp.size() == 1){
                if(temp[0] >= '1' && temp[0] <= '9'){
                    n = int(temp[0] - '1');
                }
            }
        }else if(range < 10){
            if(temp.size() == 1 && temp[0] >= '1' && temp[0] <= char(range+'0')){
                n = int(temp[0] - '1');
            }
        }cout << endl;

        if(n == -1){
            cout << "Input error. Please re-enter your choice." << endl;
            cout << "Choose a card " << str << "(1~"<< range <<"): ";
        }else
            break;
    }

    return n;
}

bool rule::End(){
    if(players[turn].handSize() == 0)
        end = true;
    return end;
}

// Operator part
Operator::Operator(poker input) : card(input){}

int Operator::operator+(Operator& add){
    int sum = 0;

    if(getShape() == 2 || getShape() == 3){
        if(getNum() == 1)
            sum += 20;
        else if(getNum() >= 9)
            sum += 10;
        else
            sum += getNum();
    }else if(getShape() == 4 && getNum() == 1)
        sum += 10;

    if(add.getShape() == 2 || add.getShape() == 3){
        if(add.getNum() == 1)
            sum += 20;
        else if(add.getNum() >= 9)
            sum += 10;
        else
            sum += add.getNum();
    }else if(add.getShape() == 4 && add.getNum() == 1)
        sum += 10;

    return sum;
}

int Operator::getNum(){
    return card.getNum();
}

int Operator::getShape(){
    return card.getShape();
}