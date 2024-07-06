#ifndef GAME_MUL
#define GAME_MUL
#include <Game.h>

// class Player;

class Multiplayer : virtual public Game {
    protected:
        static bool undoStatus;

    public:
        Multiplayer();
        void swapPlayer();
        void changeGameState(); // undo
        bool getUndoStatus();
        void setUndoStatus(bool);
};

#endif