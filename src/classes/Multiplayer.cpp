#include <Multiplayer.h>
#include <Player.h>
#include <TicTacToeFunctions.h>
#include <iostream>
#include <string>
using namespace std;

extern Game* G;

Multiplayer::Multiplayer() {
    plr1 = nullptr;
    plr2 = nullptr;
}

void Multiplayer::setPlr1(Player* plr) {
    plr1 = plr;
}

void Multiplayer::setPlr2(Player* plr) {
    plr2 = plr;
}

Player* Multiplayer::getPlr1() {
    return plr1;
}

Player* Multiplayer::getPlr2() {
    return plr2;
}

void Multiplayer::swapPlayer() {
    if (G->getCurrentPlayer() == plr1) {
        G->setCurrentPlayer(plr2);
    } else {
        G->setCurrentPlayer(plr1);
    }
}

void Multiplayer::changeGameState() { // undo
    // change the game state
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            G->getState().presState[i][j] = G->getState().prevState[i][j];
        }
    }
}

// void Multiplayer::startMulGame() {
//     // displayGameState();

//     plr1->setWins(plr1->getWins() + 1);
//     cout << plr1->getWins() << endl;
// }