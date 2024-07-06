#include <string>
#include <Player.h>
#include <TicTacToeFunctions.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>
#include <iostream>
using namespace std;
using json = nlohmann::json;

extern string chosen;
extern Game* G;
extern Player* plr1;
extern Player* plr2;

Player::Player() {
    username = "";
    plrWins = 0;
    plrLoses = 0;
    undoCount = 0;
    coins = 0;
    powerups.twoUndoMoves = false;
}

int Player::getLoses() { return plrLoses; }
int Player::getWins() { return plrWins; }
string Player::getUsername() { return username; }
char Player::getSymbol() { return symbol; }
int Player::getUndoCount() { return undoCount; }
int Player::getCoins() { return coins; }
void Player::setPowerups(string typeOfPurchase) {
    if (typeOfPurchase == "undo") {
        powerups.twoUndoMoves = true;
    }
}
PowerupPurchases Player::getPowerups() {
    return powerups;
}

void Player::setLoses(int l) { plrLoses = l; }
void Player::setWins(int w) { plrWins = w; }
void Player::setUsername(string s) { username = s; }
void Player::setSymbol(char s) { symbol = s; }
void Player::setUndoCount(int c) { undoCount = c; }
void Player::setCoins(int c) { coins = c; }

void winMul() {
    EM_ASM({
        setTimeout(function() {
            alert(UTF8ToString($0) + " wins");
        }, 10);
    }, G->getUsername().c_str());
    plr1->setIsCurrentRunning(false);
    if (G == plr1) {
        plr1->setWins(plr1->getWins() + 1);
        plr1->setCoins(plr1->getCoins() + 10);
        plr2->setLoses(plr2->getLoses() + 1);
        json j;
        j["plr1"] = {
            {"username", plr1->getUsername()},
            {"wins", plr1->getWins()},
            {"loses", plr1->getLoses()},
            {"coins", plr1->getCoins()}
        };
        j["plr2"] = {
            {"username", plr2->getUsername()},
            {"wins", plr2->getWins()},
            {"loses", plr2->getLoses()},
            {"coins", plr2->getCoins()}
        };
        string jsonStr = j.dump(4);
        string winner = j["plr1"].dump(4);
        string loser = j["plr2"].dump(4);
        updateWinnerAndLoser(winner.c_str(), loser.c_str());
        EM_ASM({
            let jsonStr = UTF8ToString($0);
            let json = JSON.parse(jsonStr);
            document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
            document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
            document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
            document.getElementById("x-coins").innerHTML = json.plr1.coins;
            document.getElementById("x-wins").innerHTML = json.plr1.wins;
            document.getElementById("x-loses").innerHTML = json.plr1.loses;
            document.getElementById("plr-2-counter-wins").innerHTML = json.plr2.username;
            document.getElementById("plr-2-counter-loses").innerHTML = json.plr2.username;
            document.getElementById("plr-2-coins").innerHTML = json.plr2.username;
            document.getElementById("o-wins").innerHTML = json.plr2.wins;
            document.getElementById("o-loses").innerHTML = json.plr2.loses;
            document.getElementById("o-coins").innerHTML = json.plr2.coins;
        }, jsonStr.c_str());
    } else {
        plr2->setWins(plr2->getWins() + 1);
        plr2->setCoins(plr2->getCoins() + 10);
        plr1->setLoses(plr1->getLoses() + 1);
        json j;
        j["plr1"] = {
            {"username", plr1->getUsername()},
            {"wins", plr1->getWins()},
            {"loses", plr1->getLoses()},
            {"coins", plr1->getCoins()}
        };
        j["plr2"] = {
            {"username", plr2->getUsername()},
            {"wins", plr2->getWins()},
            {"loses", plr2->getLoses()},
            {"coins", plr2->getCoins()}
        };
        string jsonStr = j.dump(4);
        string winner = j["plr2"].dump(4);
        string loser = j["plr1"].dump(4);
        updateWinnerAndLoser(winner.c_str(), loser.c_str());
        EM_ASM({
            let jsonStr = UTF8ToString($0);
            let json = JSON.parse(jsonStr);
            document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
            document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
            document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
            document.getElementById("x-coins").innerHTML = json.plr1.coins;
            document.getElementById("x-wins").innerHTML = json.plr1.wins;
            document.getElementById("x-loses").innerHTML = json.plr1.loses;
            document.getElementById("plr-2-counter-wins").innerHTML = json.plr2.username;
            document.getElementById("plr-2-counter-loses").innerHTML = json.plr2.username;
            document.getElementById("plr-2-coins").innerHTML = json.plr2.username;
            document.getElementById("o-wins").innerHTML = json.plr2.wins;
            document.getElementById("o-loses").innerHTML = json.plr2.loses;
            document.getElementById("o-coins").innerHTML = json.plr2.coins;
        }, jsonStr.c_str());
    }
    EM_ASM({
        let cont = document.getElementById("cont-mul");
        cont.style.visibility = "visible";
    });
}

void winAI() {
    EM_ASM({
        setTimeout(function() {
            alert(UTF8ToString($0) + " wins");
        }, 10);
    }, G->getUsername().c_str());
    plr1->setIsCurrentRunning(false);
    if (G == plr1) {
        plr1->setWins(plr1->getWins() + 1);
        plr1->setCoins(plr1->getCoins() + 10);
        plr2->setLoses(plr2->getLoses() + 1);
        json j;
        j["plr1"] = {
            {"username", plr1->getUsername()},
            {"wins", plr1->getWins()},
            {"loses", plr1->getLoses()},
            {"coins", plr1->getCoins()}
        };
        j["plr2"] = {
            {"username", plr2->getUsername()},
            {"wins", plr2->getWins()},
            {"loses", plr2->getLoses()}
        };
        string jsonStr = j.dump(4);
        string winner = j["plr1"].dump(4);
        string loser = j["plr2"].dump(4);
        updateWinnerAndLoser(winner.c_str(), loser.c_str());
        EM_ASM({
            let jsonStr = UTF8ToString($0);
            let json = JSON.parse(jsonStr);
            document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
            document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
            document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
            document.getElementById("x-coins").innerHTML = json.plr1.coins;
            document.getElementById("x-wins").innerHTML = json.plr1.wins;
            document.getElementById("x-loses").innerHTML = json.plr1.loses;
            // document.getElementById("plr-2-counter-wins").innerHTML = json.plr2.username;
            // document.getElementById("plr-2-counter-loses").innerHTML = json.plr2.username;
            // document.getElementById("plr-2-coins").innerHTML = json.plr2.username;
            document.getElementById("ai-wins").innerHTML = json.plr2.wins;
            document.getElementById("ai-loses").innerHTML = json.plr2.loses;
            // document.getElementById("o-coins").innerHTML = json.plr2.coins;
        }, jsonStr.c_str());
    } else {
        plr2->setWins(plr2->getWins() + 1);
        plr1->setLoses(plr1->getLoses() + 1);
        json j;
        j["plr1"] = {
            {"username", plr1->getUsername()},
            {"wins", plr1->getWins()},
            {"loses", plr1->getLoses()},
            {"coins", plr1->getCoins()},
        };
        j["plr2"] = {
            {"username", plr2->getUsername()},
            {"wins", plr2->getWins()},
            {"loses", plr2->getLoses()},
        };
        string jsonStr = j.dump(4);
        string winner = j["plr2"].dump(4);
        string loser = j["plr1"].dump(4);
        updateWinnerAndLoser(winner.c_str(), loser.c_str());
        EM_ASM({
            let jsonStr = UTF8ToString($0);
            let json = JSON.parse(jsonStr);
            document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
            document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
            document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
            document.getElementById("x-coins").innerHTML = json.plr1.coins;
            document.getElementById("x-wins").innerHTML = json.plr1.wins;
            document.getElementById("x-loses").innerHTML = json.plr1.loses;
            document.getElementById("ai-wins").innerHTML = json.plr2.wins;
            document.getElementById("ai-loses").innerHTML = json.plr2.loses;
        }, jsonStr.c_str());
    }
    EM_ASM({
        let cont = document.getElementById("cont-ai");
        cont.style.visibility = "visible";
    });
}

string Player::checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (state.presState[i][0] == state.presState[i][1] && state.presState[i][1] == state.presState[i][2] && state.presState[i][0] != '_') {
            if (chosen == "multiplayer") {
                winMul();
            } else {
                winAI();
            }
            return "win";
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (state.presState[0][i] == state.presState[1][i] && state.presState[1][i] == state.presState[2][i] && state.presState[0][i] != '_') {
            if (chosen == "multiplayer") {
                winMul();
            } else {
                winAI();
            }
            return "win";
        }
    }

    // Check diagonals
    if (state.presState[0][0] == state.presState[1][1] && state.presState[1][1] == state.presState[2][2] && state.presState[0][0] != '_') {
        if (chosen == "multiplayer") {
                winMul();
            } else {
                winAI();
            }
        return "win";
    }

    if (state.presState[0][2] == state.presState[1][1] && state.presState[1][1] == state.presState[2][0] && state.presState[0][2] != '_') {
        if (chosen == "multiplayer") {
                winMul();
            } else {
                winAI();
            }
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
    plr1->setIsCurrentRunning(false);

    EM_ASM({
        let cont = document.getElementById("cont-mul") || document.getElementById("cont-ai");
        cont.style.visibility = "visible";
    });

    return "draw";
}