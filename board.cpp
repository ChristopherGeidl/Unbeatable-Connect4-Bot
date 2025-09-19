#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            board[i][j] = 0;
        }
    }
}

int Board::input(int column){
    if(board[0][column-1] != 0 || 0 >= column || column > 7){
        return 0;//column full or column doesn't exist
    }
    for(int i=5; i>=0; i--){
        if(board[i][column-1] == 0){
            board[i][column-1] = turn;
            return 1;
        }
    }
    return 0;//shouldn't ever happen
}

void Board::swapTurns(){
    turn = 3 - turn; //Alternate turn between 1 and 2
}

int Board::checkWin(){
    //Horizontal Win Check
    for(int i=0; i<6; i++){
        for(int j=0; j<4; j++){//only check first 4 columns
            if(board[i][j] != 0 && 
                board[i][j] == board[i][j+1] &&
                board[i][j] == board[i][j+2] && 
                board[i][j] == board[i][j+3]){
                    return 1;
            }
        }
    }

    //Vertical Win Check
    for(int j=0; j<7; j++){
        for(int i=0; i<3; i++){//only check first 3 rows
            if(board[i][j] != 0 &&
                board[i][j] == board[i+1][j] &&
                board[i][j] == board[i+2][j] &&
                board[i][j] == board[i+3][j]){
                    return 1;
            }
        }
    }

    //Diagonal (bottom-left to top-right)
    for(int i = 3; i < 6; i++) { // Start from row 3 to row 5
        for(int j = 0; j < 4; j++) {// Only check first 4 columns
            if(board[i][j] != 0 && 
               board[i][j] == board[i-1][j+1] && 
               board[i][j] == board[i-2][j+2] && 
               board[i][j] == board[i-3][j+3]) {
                return 1;
            }
        }
    }

    //Diagonal (top-left to bottom-right)
    for(int i = 0; i < 3; i++) { // Only check first 3 rows
        for(int j = 0; j < 4; j++) { // Only check first 4 columns
            if(board[i][j] != 0 && 
               board[i][j] == board[i+1][j+1] && 
               board[i][j] == board[i+2][j+2] && 
               board[i][j] == board[i+3][j+3]) {
                return 1;
            }
        }
    }

    return false; // No winner yet

}

char Board::boardTurnToChar(int num){
    if(num == 0){
        return '.';
    }else if(num == 1){
        return 'O';
    }else{
        return 'X';
    }
}

void Board::printBoard(){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            cout << boardTurnToChar(board[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

