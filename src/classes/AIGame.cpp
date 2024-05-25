#include <AIGame.h>
#include <Player.h>
#include <iostream>
using namespace std;

AIGame::AIGame() {
    difficulty = 0; // Default difficulty
    plr1 = nullptr;
    plr2 = nullptr;
}

void AIGame::setPlr1(Player* plr) {
    plr1 = plr;
}

void AIGame::setPlr2(Player* plr) {
    plr2 = plr;
}

Player* AIGame::getPlr1() {
    return plr1;
}

Player* AIGame::getPlr2() {
    return plr2;
}

// void AIGame::startAIGame() {
//     // displayGameState();
//     plr1->setWins(plr1->getWins() + 1);
//     cout << plr1->getWins() << endl;
// }