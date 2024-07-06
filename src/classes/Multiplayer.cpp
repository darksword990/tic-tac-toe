#include <Multiplayer.h>
#include <Player.h>
#include <TicTacToeFunctions.h>
#include <iostream>
#include <string>
using namespace std;

extern Game* G;
extern Player* plr1;
extern Player* plr2;

bool Multiplayer::undoStatus;

Multiplayer::Multiplayer() {
    undoStatus = true;
    cout << "Multiplayer called" << endl;
}

bool Multiplayer::getUndoStatus() {
    return undoStatus;
}

void Multiplayer::setUndoStatus(bool val) {
    undoStatus = val;
}

void Multiplayer::swapPlayer() {
    if (G == plr1) {
        G = plr2;
    } else {
        G = plr1;
    }
}

void Multiplayer::changeGameState() { // undo
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state.presState[i][j] = state.prevState[i][j];
        }
    }
}