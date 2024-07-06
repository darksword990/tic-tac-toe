#include <AIGame.h>
#include <Multiplayer.h>
#include <Player.h>
#include <TicTacToeFunctions.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

char GameState::presState[3][3];
char GameState::prevState[3][3];

bool Game::isCurrentRunning = false;

void Game::setValues() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state.presState[i][j] = '_';
            state.prevState[i][j] = '_';
        }
    }
}

Game::Game() {
    srand(time(0));
    setValues();
    cout << "Game cons" << endl;
};

bool Game::getIsCurrentRunning() {
    return isCurrentRunning;
}

void Game::setIsCurrentRunning(bool val) {
    isCurrentRunning = val;
}