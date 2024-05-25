#ifndef GAME_PLR
#define GAME_PLR

#include <Multiplayer.h>
#include <AIGame.h>
#include <string>
using namespace std;

class Player : public Multiplayer, public AIGame {
    protected:
        string username;
        int plrWins;
        int plrLoses;
        char symbol;
        int undoCount;

    public:
        Player();
        string getUsername();
        int getWins();
        int getLoses();
        char getSymbol();
        int getUndoCount();

        void setWins(int);
        void setLoses(int);
        void setUsername(string);
        void setSymbol(char);
        void setUndoCount(int);

        string checkWinner();
};

#endif