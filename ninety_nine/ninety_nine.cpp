#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "poker.h"
#include "ninety_nine.h"

// player part
player::player(string str){
    name = str;
    point = 0;
}

string player::getName(){
    return name;
}

void player::inHand(poker get){
    hand.push_back(get);
}

void player::outHand(int n){
    hand.erase(hand.begin()+n);
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

int player::getPoint(){
    return point;
}


// rule part
rule::rule(){
    fourPlayer = false;
}

void rule::startGame(){
    turn = 0;
    forward = true;
    sum = 0;
    aDeck.shuffleCard();
    loser = 0;
    
    for(int i = 0; i < players.size(); i++){
        players[i].inHand(aDeck.dealCard());
        order.push_back(i);
        for(int j = 0; j < i; j++){
            if(players[i].getHand()[0].getNum() > players[j].getHand()[0].getNum())
                swap(order[i], order[j]);
            else if(players[i].getHand()[0].getNum() == players[j].getHand()[0].getNum())
                if(players[i].getHand()[0].getShape() > players[j].getHand()[0].getShape())
                    swap(order[i], order[j]);
        }
    }

    for(auto i : order){
        cout << players[i].getName() << ": " << endl;
        aDeck.showCard(players[i].getHand(), 1);
        cout << endl;
        aDeck.returnCard(players[i].getHand()[0]);
        players[i].outHand(0);
        for(int j = 0; j < 5; j++)
            players[i].inHand(aDeck.dealCard());
    }
}

void rule::addPlayer(int num){
    if(num >= 4)
        fourPlayer = true;
    for(int i = 0; i < num; i++){
        string str;
        cout << "Enter you name (in English): ";
        cin >> str;
        player p(str);
        players.push_back(p);
        if(i == num-1){
            cout << "Ready to start!!!" << endl;
            cout << "------------------------------" << endl << endl;
        }else
            cout << "Next player ->" << endl;
    }

}

int rule::getOrder(){
    return order.size();
}

void rule::play(){
    cout << "It's " << players[order[turn]].getName() << "'s turn." << endl;
    aDeck.showCard(players[order[turn]].getHand(), 5);
    cout << "Choose a card (1~5): ";
    int n; cin >> n;
    while(n < 1 || n > 5){
        cout << "Error. Please re-enter your chioce." << endl;
        cout << "Choose a card (1~5): ";
        cin >> n;
    }
    setSum(n-1);
    cout << endl;
}

void rule::setSum(int num){
    int n = players[order[turn]].getHand()[num].getNum();
    int s = players[order[turn]].getHand()[num].getShape();
    int nextTurn = -1;

    if(n == 1 && s == 4){
        sum = 0;
    }else if(n == 4 && fourPlayer){
        if(forward)
            forward = false;
        else
            forward = true;
    }else if(n == 5){
        int func, count = 0;
        for(auto i : order){
            cout << ++count << ". " << players[i].getName() << "  ";
        }cout << endl;
        cout << "Who do you want to choose (enter a number): ";
        cin >> func;
        while(func < 1 || func > order.size()){
            cout << "Error. Please re-enter your choice." << endl;
            cout << "Who do you want to choose (enter a number): ";
            cin >> func;
        }
        nextTurn = func-1;
    }else if(n == 10){
        if(sum < 10)
            sum += 10;
        else{
            cout << "1. Add  or  2. Sub : ";
            int func; cin >> func; 
            while(func < 1 || func > 2){
                cout << "Error. Please re-enter your chioce." << endl;
                cout << "1. Add  or  2. Sub : ";
                cin >> func;
            }
            cout << endl;
            if(func == 1){
                if(sum+10 > 99){
                    lose();
                    return;
                }
                else
                    sum += 10;
            }else if(func == 2){
                sum -= 10;
            }
        }
    }else if(n == 11){

    }else if(n == 12){
        if(sum < 20)
            sum += 20;
        else{
            cout << "1. Add  or  2. Sub : ";
            int func; cin >> func; 
            while(func < 1 || func > 2){
                cout << "Error. Please re-enter your chioce." << endl;
                cout << "1. Add  or  2. Sub : ";
                cin >> func;
            }
            cout << endl;
            if(func == 1){
                if(sum+20 > 99){
                    lose();
                    return;
                }
                else
                    sum += 20;
            }else if(func == 2){
                sum -= 20;
            }
        }
    }else if(n == 13){
        sum = 99;
    }else{
        if(sum+n > 99){
            lose();
            return;
        }else
            sum += n;
    }

    cout << "sum = " << sum << endl;
    aDeck.returnCard(players[order[turn]].getHand()[num]);
    players[order[turn]].outHand(num);
    players[order[turn]].inHand(aDeck.dealCard());
    if(n == 5)
        turn = nextTurn;
    else
        checkForward();

}

void rule::checkForward(){
    if(forward)
        turn++;
    else
        turn--;

    checkTurn();
}

void rule::checkTurn(){
    if(turn >= order.size())
        if(forward)
            turn = 0;
        else
            turn = order.size()-1;
    else if(turn < 0)
        if(forward)
            turn = order.size()-1;
        else
            turn = 0;
}

void rule::exitGame(){
    for(auto i : players[order[turn]].getHand()){        
        aDeck.returnCard(i);
    }players[order[turn]].eraseHand();
    players[order[turn]].setPoint(++loser);
    order.erase(order.begin()+turn);
}

void rule::lose(){
    cout << " You Lose. TAT" << endl;
    exitGame();
    if(!forward)
        turn--;
    checkTurn();
}

void rule::win(){
    cout << "Congratulation!! " << players[order[turn]].getName() << " is the winner!!" << endl;
    exitGame();
    getPoint();
}

void rule::getPoint(){
    cout << endl;
    cout << "Points" << endl;
    for(auto i : players)
        cout << i.getName() << ": " << i.getPoint() << endl;
    cout << "------------------------------" << endl << endl;
}

void rule::rank(){
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