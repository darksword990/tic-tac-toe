#include <string>
#include <Player.h>
#include <TicTacToeFunctions.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>
#include <iostream>
using namespace std;
using json = nlohmann::json;

extern Game* G;
extern Multiplayer* Mul;
extern AIGame* AI;
extern Player* plr1;
extern Player* plr2;

Player::Player() {
    plrWins = 0;
    plrLoses = 0;
    undoCount = 0;
}

int Player::getLoses() { return plrLoses; }
int Player::getWins() { return plrWins; }
string Player::getUsername() { return username; }
char Player::getSymbol() { return symbol; }
int Player::getUndoCount() { return undoCount; }

void Player::setLoses(int l) { plrLoses = l; }
void Player::setWins(int w) { plrWins = w; }
void Player::setUsername(string s) { username = s; }
void Player::setSymbol(char s) { symbol = s; }
void Player::setUndoCount(int c) { undoCount = c; }

void win() {
    EM_ASM({
        setTimeout(function() {
            alert(UTF8ToString($0) + " wins");
        }, 10);
    }, G->getCurrentPlayer()->getUsername().c_str());
    G->setIsCurrentRunning(false);
    EM_ASM({
        let cont = document.getElementById("cont-mul");
        cont.style.visibility = "visible";
    });
}

string Player::checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (state.presState[i][0] == state.presState[i][1] && state.presState[i][1] == state.presState[i][2] && state.presState[i][0] != '_') {
            // cout << state.presState[i][0] << state.presState[i][1] << state.presState[i][2] << endl;
            win();
            return "win";
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (state.presState[0][i] == state.presState[1][i] && state.presState[1][i] == state.presState[2][i] && state.presState[0][i] != '_') {
            // cout << "col" << endl;
            // cout << state.presState[0][i] << state.presState[1][i] << state.presState[2][i] << endl;
            win();
            return "win";
        }
    }

    // Check diagonals
    if (state.presState[0][0] == state.presState[1][1] && state.presState[1][1] == state.presState[2][2] && state.presState[0][0] != '_') {
        // cout << "diag" << endl;
        // cout << state.presState[0][0] << state.presState[1][1] << state.presState[2][2] << endl;
        win();
        return "win";
    }

    if (state.presState[0][2] == state.presState[1][1] && state.presState[1][1] == state.presState[2][0] && state.presState[0][2] != '_') {
        // cout << "diag" << endl;
        // cout << state.presState[0][2] << state.presState[1][1] << state.presState[2][0] << endl;
        win();
        return "win";
    }

    string str = "";

    // check for draw
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str += state.presState[i][j];
        }
    }

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '_') {
            return "continue";
        }
    }

    EM_ASM({
        setTimeout(function() {
            alert("It's a draw");
        }, 0);
    });
    G->setIsCurrentRunning(false);

    return "draw";
}