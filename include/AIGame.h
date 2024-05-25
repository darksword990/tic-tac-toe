#ifndef GAME_AI
#define GAME_AI
#include <Game.h>

class Player;

class AIGame : virtual public Game {
    protected:
        int difficulty;
        Player* plr1;
        Player* plr2;
        
    public:
        AIGame();
        void setPlr1(Player*);
        void setPlr2(Player*);
        Player* getPlr1();
        Player* getPlr2();
        // void startAIGame();
};

#endif