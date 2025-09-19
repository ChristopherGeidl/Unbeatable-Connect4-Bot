#include <iostream>
#include <list>
#include "Board.h"
#include "Bot.h"
using namespace std;

//minimax with optimizations: explore all future moves
//alpha-beta pruning (get rid of guarenteed bad)
//transposition table: (stores results to avoid repeated calculations)

int Bot::evaluate(Board &b){
    if(b.checkWin()){
        if(b.getTurn() == 1){
            return 1000000; //bot wins
        }else{
            return -1000000; //player wins
        }
    }

    int score = 0;
    //Center column has most win conditions:
    for(int i=0; i<6; i++){
        if(b.getBoardIJ(i,4) == 1){
            score += 3;
        }else if(b.getBoardIJ(i,4) == 2){
            score -=3;
        }
    }

    // Horizontal windows of 4 ################ Doesn't check if unblocked #####################
    for(int i=0; i<6; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i, j + k);
                if(cell == 1){
                    botPieces++;
                }else if(cell == 2){
                    playerPieces++;
                }
            }

            if(botPieces > 0 && playerPieces == 0){
                if(botPieces == 2){
                    score += 10;
                }
                else if(botPieces == 3){
                    score += 50;
                }
            } else if(playerPieces > 0 && botPieces == 0) {
                if(playerPieces == 2){
                    score -= 10;
                }
                else if(playerPieces == 3){
                    score -= 80;
                }
            }
        }
    }
    // Vertical windows of 4
    for(int j=0; j<7; j++){
        for(int i=0; i<4; i++){
            int botPieces = 0;
            int playerPieces = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i + k, j);
                if(cell == 1){
                    botPieces++;
                }else if(cell == 2){
                    playerPieces++;
                }
            }

            if(botPieces > 0 && playerPieces == 0){
                if(botPieces == 2){
                    score += 10;
                }
                else if(botPieces == 3){
                    score += 50;
                }
            } else if(playerPieces > 0 && botPieces == 0) {
                if(playerPieces == 2){
                    score -= 10;
                }
                else if(playerPieces == 3){
                    score -= 80;
                }
            }
        }
    }
    //positive slope diagonals
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i+k, j+k);
                if(cell == 1){
                    botPieces++;
                }else if(cell == 2){
                    playerPieces++;
                }
            }

            if(botPieces > 0 && playerPieces == 0){
                if(botPieces == 2){
                    score += 10;
                }
                else if(botPieces == 3){
                    score += 50;
                }
            } else if(playerPieces > 0 && botPieces == 0) {
                if(playerPieces == 2){
                    score -= 10;
                }
                else if(playerPieces == 3){
                    score -= 80;
                }
            }
        }
    }
    //negative slope diagonals
    for(int i=3; i<6; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i - k, j + k);
                if(cell == 1){
                    botPieces++;
                }else if(cell == 2){
                    playerPieces++;
                }
            }

            if(botPieces > 0 && playerPieces == 0){
                if(botPieces == 2){
                    score += 10;
                }
                else if(botPieces == 3){
                    score += 50;
                }
            } else if(playerPieces > 0 && botPieces == 0) {
                if(playerPieces == 2){
                    score -= 10;
                }
                else if(playerPieces == 3){
                    score -= 80;
                }
            }
        }
    }
    return score; 
}

int Bot::minimax(Board &b, int depth, int alpha, int beta, int maximizingPlayer){
    if(depth == 0 || b.checkWin()){
        return evaluate(b);
    }

    if(maximizingPlayer){
        int value = -1000000;
        for(int j=1; j<=7; j++){
            Board temp = b;
            if(temp.input(j)){
                temp.swapTurns();
                value = max(value, minimax(temp, depth-1, alpha, beta, 0));
                if(value >= beta){
                    break; //prune beta
                }
                alpha = max(alpha, value);
            }
        }
        return value;
    }else{
        int value = 1000000;
        for(int j=1; j<=7; j++){
            Board temp = b;
            if(temp.input(j)){
                temp.swapTurns();
                value = min(value, minimax(temp, depth-1, alpha, beta, 1));
                if(value <= alpha){
                    break; //prune alpha
                }
                beta = min(beta, value);
            }
        }
        return value;
    }
}

int Bot::play(Board b){
    int bestMove = 4;//first move should be 4
    int bestScore = -1000000;

    for(int j=1; j<=7; j++){
        Board temp = b;
        if(temp.input(j)){
            temp.swapTurns();
            int score = minimax(temp, 8, -1000000, 1000000, 1);//depth=6
            if(score > bestScore){
                bestScore = score;
                bestMove = j;
            }
        }
    }
    return bestMove;
}
