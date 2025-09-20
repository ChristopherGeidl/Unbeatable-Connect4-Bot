#ifndef BOT_H
#define BOT_H

class Bot{
    public:
        Bot(int playerNum){ player = playerNum; };
        Bot(int playerNum, int playCol4First){ isFirstTurn = 1- playCol4First; };
        int play(Board);
    private:
        Board board;
        int player;
        int isFirstTurn = 1;
        int evaluate(Board&);
        int minimax(Board&, int, int, int, int);
};

#endif