#ifndef GAME_MUL
#define GAME_MUL
#include <Game.h>

class Player;

class Multiplayer : virtual public Game {
    protected:
        Player* plr1;
        Player* plr2;

    public:
        Multiplayer();
        void setPlr1(Player*);
        void setPlr2(Player*);
        Player* getPlr1();
        Player* getPlr2();
        void swapPlayer();
        // void startMulGame();
        void changeGameState(); // undo
};

#endif