#include <iostream>
#include "Board.h"
#include "Bot.h"
using namespace std;

int main(){
    Board b;
    int col = 0; //input variable
    int validInput = false;
    b.swapTurns();
    while(!b.checkWin()){
        b.swapTurns();
        cout << "Player " << b.boardTurnToChar(b.getTurn()) << endl;
        b.printBoard();
        while(!validInput){
            cout << "Enter Column Number:";
            cin >> col;
            if(b.input(col)){
                validInput = true;
            }
        }
        validInput = false;
        cout << endl;
    }

    b.printBoard();
    cout << "!! PLAYER " << b.boardTurnToChar(b.getTurn()) << " WINS !!" << endl;
}