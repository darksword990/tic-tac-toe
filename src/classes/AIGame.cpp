#include <AIGame.h>
#include <Player.h>
#include <iostream>
using namespace std;

extern Player* plr1;
extern Player* plr2;

int AIGame::difficulty;
int AIGame::winEval;
int AIGame::loseEval;

AIGame::AIGame() {
    difficulty = 0;
    winEval = 10;
    loseEval = -10;
    cout << "AIGame cons" << endl;
}

void AIGame::setDifficulty(int diff) {
    difficulty = diff;
}

int AIGame::getDifficulty() {
    return difficulty;
}

bool AIGame::movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state.presState[i][j] == '_')
                return true;
    return false;
}

int AIGame::evaluationFunctionAtTerminalState() {
    for (int row = 0; row < 3; row++) {
        if (state.presState[row][0] == state.presState[row][1] && state.presState[row][1] == state.presState[row][2]) {
            if (state.presState[row][0] == plr2->getSymbol())
                return winEval;
            else if (state.presState[row][0] == plr1->getSymbol())
                return loseEval;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (state.presState[0][col] == state.presState[1][col] && state.presState[1][col] == state.presState[2][col]) {
            if (state.presState[0][col] == plr2->getSymbol())
                return winEval;
            else if (state.presState[0][col] == plr1->getSymbol())
                return loseEval;
        }
    }

    if (state.presState[0][0] == state.presState[1][1] && state.presState[1][1] == state.presState[2][2]) {
        if (state.presState[0][0] == plr2->getSymbol())
            return winEval;
        else if (state.presState[0][0] == plr1->getSymbol())
            return loseEval;
    }

    if (state.presState[0][2] == state.presState[1][1] && state.presState[1][1] == state.presState[2][0]) {
        if (state.presState[0][2] == plr2->getSymbol())
            return winEval;
        else if (state.presState[0][2] == plr1->getSymbol())
            return loseEval;
    }

    return 0;
}

int AIGame::minimax(char ticTacToeBoard[3][3], int currentPositionOfTree, bool isItMaximizer) {
    int points = evaluationFunctionAtTerminalState();

    if (points == winEval) {
        return points - currentPositionOfTree;
    }

    if (points == loseEval) {
        return points + currentPositionOfTree;
    }

    if (!movesLeft()) {
        return 0;
    }

    if (currentPositionOfTree == difficulty) {
        return points;
    }

    if (isItMaximizer) {
        int bestPoint = INT_MIN;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state.presState[i][j] == '_') {
                    state.presState[i][j] = plr2->getSymbol();

                    bestPoint = max(bestPoint, minimax(state.presState, currentPositionOfTree + 1, !isItMaximizer));

                    state.presState[i][j] = '_';
                }
            }
        }
        return bestPoint;
    } else {
        int bestPoint = INT_MAX;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state.presState[i][j] == '_') {
                    state.presState[i][j] = plr1->getSymbol();

                    bestPoint = min(bestPoint, minimax(state.presState, currentPositionOfTree + 1, !isItMaximizer));

                    state.presState[i][j] = '_';
                }
            }
        }
        return bestPoint;
    }
}

AINextMove AIGame::findAIBestNextMove() {
    int bestCurrentMove = INT_MIN;
    AINextMove bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.presState[i][j] == '_') {
                state.presState[i][j] = plr2->getSymbol();

                int computeCurrentMove = minimax(state.presState, 0, false);

                state.presState[i][j] = '_';

                if (computeCurrentMove > bestCurrentMove) {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestCurrentMove = computeCurrentMove;
                }
            }
        }
    }

    return bestMove;
}