#ifndef GAME_H
#define GAME_H
#include <TicTacToeFunctions.h>
#include <string>
#include "../src/structs/GameState.cpp"
using namespace std;

class Game {
protected:
    GameState state;
    static bool isCurrentRunning;

public:
    Game(); // constructor
    void setValues();
    GameState getState() {
        return state;
    }
    virtual string getUsername() = 0;
    virtual int getWins() = 0;
    virtual int getLoses() = 0;
    virtual char getSymbol() = 0;
    virtual int getUndoCount() = 0;
    virtual int getCoins() = 0;
    virtual void setWins(int) = 0;
    virtual void setLoses(int) = 0;
    virtual void setUsername(string) = 0;
    virtual void setSymbol(char) = 0;
    virtual void setUndoCount(int) = 0;
    virtual void setCoins(int) = 0;
    virtual string checkWinner() = 0;
    virtual void setPowerups(string) = 0;
    virtual PowerupPurchases getPowerups() = 0;
    bool getIsCurrentRunning();
    void setIsCurrentRunning(bool);
};

#endif