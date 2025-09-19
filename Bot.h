#ifndef BOT_H
#define BOT_H

class Bot{
    public:
        int play(Board);
    private:
        Board board;
        int evaluate(Board&);
        int minimax(Board&, int, int, int, int);
};

#endif