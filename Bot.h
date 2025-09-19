#ifndef BOT_H
#define BOT_H

class Bot{
    public:
        Bot(Board);
        int play();
    private:
        Board board;
        int numTurns;
};

#endif