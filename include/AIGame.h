#ifndef GAME_AI
#define GAME_AI
#include <Game.h>

// class Player;

class AIGame : virtual public Game {
    protected:
        static int difficulty;
        static int winEval;
        static int loseEval;
        
    public:
        AIGame();
        void setDifficulty(int);
        int getDifficulty();
        int evaluationFunctionAtTerminalState();
        int minimax(char[3][3], int, bool); // depth, isMax
        bool movesLeft();
        AINextMove findAIBestNextMove();
};

#endif