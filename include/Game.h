#ifndef GAME_H
#define GAME_H
#include <TicTacToeFunctions.h>
#include "../src/structs/GameState.cpp"
class Player;

class Game {
    protected:
        GameState state;
        bool isCurrentRunning;
        Player* currentPlayer;
        bool undoStatus;

public:
    Game(); // constructor
    // static char* displayGameState(int*, int*);
    void display();
    void setValues();
    GameState getState() {
        return state;
    }
    void setState(GameState state) {
        this->state = state;
    }
    void setCurrentPlayer(Player*);
    Player* getCurrentPlayer();
    bool getIsCurrentRunning();
    void setIsCurrentRunning(bool);
    bool getUndoStatus();
    void setUndoStatus(bool);
    // void run();
};

#endif