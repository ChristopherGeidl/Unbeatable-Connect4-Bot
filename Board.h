#ifndef BOARD_H
#define BOARD_H

class Board{
    public:
        Board();
        int input(int);
        int getTurn(){ return turn; } 
        int getBoardIJ(int i, int j){ return board[i][j]; }
        int checkWin();
        void printBoard();
        char boardTurnToChar(int);
        void swapTurns();
    private:
        int board[6][7];
        int turn = 1;
};

#endif