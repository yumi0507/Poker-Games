#include <iostream>
#include <string>
#include <vector>
#include "poker.h"
#include "ninety_nine.h"
using namespace std;

int main(){
    cout << "People in a play: ";
    int n; cin >> n;
    rule game;
    game.addPlayer(n);

    while(true){
        game.startGame();
        while(game.getOrder()){
            if(game.getOrder() == 1){
                game.win();
                break;
            }
            game.play();

        }

        int func;
        while(true){
            cout << endl;
            cout << "1. Continue the game" << endl;
            cout << "2. End the game" << endl;
            cout << "Which do you choose? Enter the number: ";
            cin >> func;
            if(func == 1 || func == 2)
                break;
        }

        if(func == 2){
            game.rank();
            break;
        }
    }
   
    system("pause");
}