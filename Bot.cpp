#include <iostream>
#include "Board.h"
#include "Bot.h"
using namespace std;

Bot::Bot(Board b){
    board = b;
}

int Bot::play(){
    if(numTurns == 0){
        return 4; //play center col
    }
    return 1;
}
