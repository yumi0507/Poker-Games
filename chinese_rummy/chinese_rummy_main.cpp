#include <iostream>
#include <string>
#include <vector>
#include "chinese_rummy.h"
using namespace std;

int main(){
    cout << "People in a play(2~4): ";
    char n = 'a';
    while(n <= '2' || n >= '4'){
        cin >> n;
        cout << endl;
        if(n >= '2' && n <= '4')
            break;
        cout << "Input error. Please re-enter the number: ";
    }
    rule game;
    game.addPlayer(int(n-'0'));

    while(true){
        game.startGame();

        while(!game.End()){
            game.play();
        }
        game.rank();

        cout << "1. Start a new game" << endl;
        cout << "2. Eixt" << endl;
        cout << "Choose the number: ";
        char func = 'a'; 
        while(true){
            cin >> func;
            cout << endl;
            if(func == '1' || func == '2')
                break;
            cout << "Input error. Please re-enter your choice: ";
        }

        if(func == '1')
            system("cls");
        else if(func == '2')
            break;

    }
}