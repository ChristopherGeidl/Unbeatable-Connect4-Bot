#ifndef BOT_H
#define BOT_H

class Bot{
    public:
        Bot(Board);
        int play();
    private:
        Board board;
        int firstTurn = 1;
        int evaluate(Board&);
        int minimax(Board&, int, int, int, int);
};

#endif