#include <iostream>

class Board{
    public:
        Board();
    private:
        int board[6][7];
        int turn = 1;

        int input(int);
        int getTurn(){ return turn; } 
        void printBoard();
};

Board::Board(){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            board[i][j] == 0;
        }
    }
}

int Board::input(int column){
    if(board[0][column-1] != 0){
        return 0;//column full
    }
    for(int i=5; i>=0; i--){
        if(board[i][column-1] == 0){
            board[i][column-1] = turn;
        }
    }
    //check win condition #################################
}

void Board::printBoard(){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

