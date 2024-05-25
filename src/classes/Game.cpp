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

// EM_JS(void, testFunc, (), {
//     // Assuming a 2D array like this

// // Initialize an empty 2D array for the 3x3 grid
// const gridArray = [[], [], []];

// // Iterate over each grid item


// let flattenedArray = gridArray.flat();
// let charCodes = flattenedArray.map(char => char.charCodeAt(0));

// let arrayPtr = Module._malloc(charCodes.length * Int8Array.BYTES_PER_ELEMENT);

// // Copy the flattened array data to the allocated memory
// Module.HEAP8.set(charCodes, arrayPtr / Int8Array.BYTES_PER_ELEMENT);
// console.log(gridArray);
// // Call the C++ function
// Module._print2DArray(arrayPtr, gridArray[0].length, gridArray.length);

// // Free the allocated memory
// Module._free(arrayPtr);

// });

// extern "C" {
//     EMSCRIPTEN_KEEPALIVE void print2DArray(char* arrayPtr, int width, int height) {
//         for (int y = 0; y < height; y++) {
//             for (int x = 0; x < width; x++) {
//                 // Calculate the correct index in the 1D array representation
//                 int index = y * width + x;
//                 cout << arrayPtr[index] << " ";
//             }
//             cout << endl;
//         }
//     }

//     EMSCRIPTEN_KEEPALIVE char* changeCharArray(char* charArr) {
        
//     }

//     EMSCRIPTEN_KEEPALIVE void printArr() {
//         testFunc();
//     }
// }

void Game::setValues() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state.presState[i][j] = '_';
            state.prevState[i][j] = '_';
        }
    }
}

void Game::setCurrentPlayer(Player* plr) {
    currentPlayer = plr;
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

bool Game::getUndoStatus() {
    return undoStatus;
}

void Game::setUndoStatus(bool val) {
    undoStatus = val;
}

Game::Game() {
    srand(time(0));
    setValues();
    undoStatus = true;
};

bool Game::getIsCurrentRunning() {
    return isCurrentRunning;
}

void Game::setIsCurrentRunning(bool val) {
    isCurrentRunning = val;
}

// EM_JS(void, displayGame, (), {
//     let gridItems = document.querySelectorAll(".grid-container .grid-item");
//     let wrapper = Module.cwrap("displayGameState", "number", ["number", "number"]);
//     let rowPtr = Module._malloc(Int32Array.BYTES_PER_ELEMENT);
//     let colPtr = Module._malloc(Int32Array.BYTES_PER_ELEMENT);
//     let func = wrapper(rowPtr, colPtr);

//     let row = Module.HEAP32[rowPtr / Int32Array.BYTES_PER_ELEMENT];
//     let col = Module.HEAP32[colPtr / Int32Array.BYTES_PER_ELEMENT];

//     for (let i = 0; i < row; i++) {
//         for (let j = 0; j < col; j++) {
//             let index = i * row + j;
//             gridItems[index].innerHTML = String.fromCharCode(Module.HEAP8[func + index]);
//         }
//     }

//     Module._free(rowPtr);
//     Module._free(colPtr);
// });

void Game::display() {
    // displayGame();
}

// EM_JS(const char*, acceptInput, (), {
//     let input = document.getElementById("text-input").value
//     return input;
// })

// EM_JS(void, changeHTML, (string state), {
//     if (state == "0") {

//     }
// });

// void Game::run()
// {
    // storeDataInIndexedDB("TicTacToe", "PlayerData", "Ali");
    // changeHTML("0");
    // testFunc();
    // display();

// }