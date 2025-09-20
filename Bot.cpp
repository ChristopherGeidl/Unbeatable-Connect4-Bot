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
        if(b.getTurn() == 3 - player){
            return 1000000; //bot wins
        }else{
            return -1000000; //player wins
        }
    }

    int score = 0;
    //Center column has most win conditions:
    for(int i=0; i<6; i++){
        if(b.getBoardIJ(i,4) == 1){
            score += 10;
        }else if(b.getBoardIJ(i,4) == 2){
            score -= 10;
        }
    }

    // Horizontal windows of 4
    for(int i=0; i<6; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            int empty = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i, j + k);
                if(cell == player){
                    botPieces++;
                }else if(cell == 3 - player){
                    playerPieces++;
                }else{
                    empty++;
                }
            }

            if(botPieces == 3 && empty == 1){ score += 100; }
            if(botPieces == 2 && empty == 2){ score += 10; }
            if(playerPieces == 3 && botPieces == 1){ score += 500; }
            if(playerPieces == 2 && botPieces == 1){ score += 50; }

            if(playerPieces == 3 && empty == 1){ score -= 500; }
            if(playerPieces == 2 && empty == 2){ score -= 10; }

        }
    }
    // Vertical windows of 4
    for(int j=0; j<7; j++){
        for(int i=0; i<4; i++){
            int botPieces = 0;
            int playerPieces = 0;
            int empty = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i + k, j);
                if(cell == player){
                    botPieces++;
                }else if(cell == 3 - player){
                    playerPieces++;
                }else{
                    empty++;
                }
            }

            if(botPieces == 3 && empty == 1){ score += 100; }
            if(botPieces == 2 && empty == 2){ score += 10; }
            if(playerPieces == 3 && botPieces == 1){ score += 500; }
            if(playerPieces == 2 && botPieces == 1){ score += 50; }

            if(playerPieces == 3 && empty == 1){ score -= 500; }
            if(playerPieces == 2 && empty == 2){ score -= 10; }
        }
    }
    //positive slope diagonals
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            int empty = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i+k, j+k);
                if(cell == player){
                    botPieces++;
                }else if(cell == 3 - player){
                    playerPieces++;
                }else{
                    empty++;
                }
            }

            if(botPieces == 3 && empty == 1){ score += 100; }
            if(botPieces == 2 && empty == 2){ score += 10; }
            if(playerPieces == 3 && botPieces == 1){ score += 500; }
            if(playerPieces == 2 && botPieces == 1){ score += 50; }

            if(playerPieces == 3 && empty == 1){ score -= 500; }
            if(playerPieces == 2 && empty == 2){ score -= 10; }
        }
    }
    //negative slope diagonals
    for(int i=3; i<6; i++){
        for(int j=0; j<4; j++){
            int botPieces = 0;
            int playerPieces = 0;
            int empty = 0;
            for(int k=0; k<4; k++){
                int cell = b.getBoardIJ(i - k, j + k);
                if(cell == player){
                    botPieces++;
                }else if(cell == 3 - player){
                    playerPieces++;
                }else{
                    empty++;
                }
            }

            if(botPieces == 3 && empty == 1){ score += 100; }
            if(botPieces == 2 && empty == 2){ score += 10; }
            if(playerPieces == 3 && botPieces == 1){ score += 500; }
            if(playerPieces == 2 && botPieces == 1){ score += 50; }

            if(playerPieces == 3 && empty == 1){ score -= 500; }
            if(playerPieces == 2 && empty == 2){ score -= 10; }
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
    int bestMove = 4;//in ties center should win
    int bestScore = -1000000;
    //Force first move center (in a perfect game this will force the bot to win)
    if(isFirstTurn){
        isFirstTurn = 0;
        return 4;
    }

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
