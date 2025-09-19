#include <iostream>
#include <list>
#include "Board.h"
#include "Bot.h"
using namespace std;

Bot::Bot(Board b){
    board = b;
}
//minimax with optimizations: explore all future moves
//alpha-beta pruning (get rid of guarenteed bad)
//transposition table: (stores results to avoid repeated calculations)

int Bot::evaluate(Board &b){
    if(b.checkWin() && b.getTurn() == 1){//bot wins
        return 1000000;
    }else if(b.checkWin() && b.getTurn() == 2){//player wins
        return -1000000;
    }
    return 0; //TODO: add heuristics (like favor center column, 2-in-row, etc)
}

int Bot::minimax(Board &b, int depth, int alpha, int beta, int maximizingPlayer){
    if(depth == 0 || b.checkWin()){
        return evaluate(b);
    }

    if(maximizingPlayer){
        int maxEval = -1000000;
        for(int j=1; j<=7; j++){
            Board temp = b;
            if(temp.input(j)){
                temp.swapTurns();
                int eval = minimax(temp, depth-1, alpha, beta, 1);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if(beta <= alpha){
                    break; //prune ##########################################
                }
            }
        }
        return maxEval;
    }else{
        int minEval = 1000000;
        for(int j=1; j<=7; j++){
            Board temp = b;
            if(temp.input(j)){
                temp.swapTurns();
                int eval = minimax(temp, depth-1, alpha, beta, 0);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if(beta <= alpha){
                    break; //prune #############################
                }
            }
        }
        return minEval;
    }
}

int Bot::play(){
    int bestMove = 4;//first move should be 4
    int bestScore = -1000000;

    for(int j=1; j<=7; j++){
        Board temp = board;
        if(temp.input(j)){
            temp.swapTurns();
            int score = minimax(temp, 6, -1000000, 1000000, 0);//depth=6
            if(score > bestScore){
                bestScore = score;
                bestMove = j;
            }
        }
    }
    return bestMove;
}
