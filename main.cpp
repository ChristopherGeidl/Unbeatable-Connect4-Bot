#include <iostream>
#include "Board.h"
#include "Bot.h"
using namespace std;

int main(){
    Board b;
    Bot bot(1);
    int col = 0; //input variable
    int validInput = false;
    b.swapTurns();
    while(!b.checkWin()){
        b.swapTurns();
        cout << "Player " << b.boardTurnToChar(b.getTurn()) << "'s Turn" << endl;
        b.printBoard();
        if(b.getTurn() == 1){
            b.input(bot.play(b));
        }else{
            while(!validInput){
                cout << "Enter Column Number:";
                cin >> col;
                if(b.input(col)){
                    validInput = true;
                }
            }
        }
        validInput = false;
        cout << endl;
    }
    
    //bot vs bot while loop (the first bot will always win)
    /*Bot bot2(2, 0);
    while(!b.checkWin()){
        b.swapTurns();
        cout << "Player " << b.boardTurnToChar(b.getTurn()) << "'s Turn" << endl;
        b.printBoard();
        if(b.getTurn() == 1){
            b.input(bot.play(b));
        }else{
            b.input(bot2.play(b));
        }
        cout << endl;
    }*/

    b.printBoard();
    cout << "!! PLAYER " << b.boardTurnToChar(b.getTurn()) << " WINS !!" << endl;
}