#include <TicTacToeFunctions.h>
#include <emscripten.h>
#include <Multiplayer.h>
#include <AIGame.h>
#include <Player.h>
#include <Game.h>
#include <iostream>
#include <cstring>
using namespace std;

extern Game* G;
extern Multiplayer* Mul;
extern AIGame* AI;
extern Player* plr1;
extern Player* plr2;

EM_JS(void, updateJSState, (), {
    // send the updated game state to C++ in string form
    let gridItems = document.querySelectorAll(".grid-container .grid-item");
    let arr = "";
    for (let i = 0; i < gridItems.length; i++) {
        arr += gridItems[i].innerText;
    }
    Module.ccall("updateGameState", null, ["string", "number", "number"], [arr, arr.length, 3]);
});

EM_JS(void, plrData, (int num, const char *indicator, const char *username, const char *password), {
    const openRequest = indexedDB.open("TicTacToe", 1);

    let u = UTF8ToString(username);
    let p = UTF8ToString(password);

    // Create the schema in the upgradeneeded event
    openRequest.onupgradeneeded = function(e)
    {
        const db = e.target.result;
        if (!db.objectStoreNames.contains("PlayerData"))
        {
            db.createObjectStore("PlayerData", {keyPath : 'username'});
        }
    };

    openRequest.onerror = function(e)
    {
        console.error('Error opening database:', e.target.error);
    };

    openRequest.onsuccess = function(e)
    {
        const db = e.target.result;

        // Create a transaction to write data
        const transaction = db.transaction("PlayerData", 'readwrite');

        // Get the object store from the transaction
        const store = transaction.objectStore("PlayerData");

        let d = store.get(u);

        d.onsuccess = function()
        {
            if (d.result != undefined && d.result.username == u)
            {
                if (!(d.result.password == p))
                {
                    alert("Incorrect Password, please enter again!");
                    return;
                }
                alert("Successfully logged in!");
                document.getElementById(`player${num}-login`).style.visibility = "hidden";
                Module.ccall("setPlr", null, [ "number", "string", "string", "number", "number" ], [ num, UTF8ToString(indicator), d.result.username, d.result.currentWins, d.result.currentLoses ]);
            }
            else
            {
                let usrData = {
                    username : u,
                    password : p,
                    currentWins : 0,
                    currentLoses : 0,
                    achievements : []
                };

                const request = store.put(usrData);

                request.onerror = function(e)
                {
                    console.error('Error storing data:', e.target.error);
                };

                request.onsuccess = function()
                {
                    console.log('Data stored successfully!');
                    document.getElementById(`player${num}-login`).style.visibility = "hidden";
                    Module.ccall("setPlr", null, [ "number", "string", "string", "number", "number" ], [ num, UTF8ToString(indicator), u, 0, 0 ]);
                };
            };
        }
    };
});

void refreshData() {
    if (G != nullptr) {
        cout << "Game deleted" << endl;
        delete G;
        G = nullptr;
    }
    if (Mul != nullptr) {
        cout << "Multiplayer deleted" << endl;
        delete Mul;
        Mul = nullptr;
    }
    if (AI != nullptr) {
        cout << "AI deleted" << endl;
        delete AI;
        AI = nullptr;
    }
    if (plr1 != nullptr) {
        cout << "Player 1 deleted" << endl;
        delete plr1;
        plr1 = nullptr;
    }
    if (plr2 != nullptr) {
        cout << "Player 2 deleted" << endl;
        delete plr2;
        plr2 = nullptr;
    }
}

void LoginUser1(int num, const char* indicator, const char* username, const char* password) {
    plrData(num, indicator, username, password);
    // static Player* plr1 = new Player();
    // Multiplayer::setPlr1(plr1);
}

void LoginUser2(int num, const char* indicator, const char* username, const char* password) {
    plrData(num, indicator, username, password);
    // Multiplayer* M = makeMultiplayer();
    // static Player* plr2 = new Player();
    // Multiplayer::setPlr2(plr2);
}

void setCurrentPlrAtBegin() {
    if (Mul->getPlr1()->getUsername().length() > 0 && Mul->getPlr2()->getUsername().length() > 0) {
        //generate random number between 1 and 2
        int random = rand() % 2 + 1;
        if (random == 1) {
            G->setCurrentPlayer(Mul->getPlr1());
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(X)";
            }, G->getCurrentPlayer()->getUsername().c_str());
        } else {
            G->setCurrentPlayer(Mul->getPlr2());
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                console.log(currentPlrHeading);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(O)";
            }, G->getCurrentPlayer()->getUsername().c_str());
        }
        cout << G->getCurrentPlayer()->getUsername() << endl;
        cout << G->getCurrentPlayer()->getSymbol() << endl;
        G->setIsCurrentRunning(true);
    }
}

void setCurrentPlr(Player* plr) {
    G->setCurrentPlayer(plr);
}

void updateGameState(const char* arr, int length, int size) {
    // Reconstruct the 2D array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // arr[i*size + j] calculates 2D index from 1D index
            GameState::presState[i][j] = arr[i*size + j];
        }
    }
}

void setPlr(int num, const char* indicator, const char* username, int wins, int loses) {
    string ind = indicator;
    if (ind == "2") {
        if (num == 1) {
            plr1 = new Player();
            plr1->setUsername(username);
            plr1->setWins(wins);
            plr1->setLoses(loses);
            plr1->setSymbol('X');
            Mul->setPlr1(plr1);
        } else {
            plr2 = new Player();
            plr2->setUsername(username);
            plr2->setWins(wins);
            plr2->setLoses(loses);
            plr2->setSymbol('O');
            Mul->setPlr2(plr2);
        }
        // if (Mul->getPlr1()->getUsername().length() > 0 && Mul->getPlr2()->getUsername().length() > 0) {
        //     //generate random number between 1 and 2
        //     int random = rand() % 2 + 1;
        //     if (random == 1) {
        //         G->setCurrentPlayer(Mul->getPlr1());
        //     } else {
        //         G->setCurrentPlayer(Mul->getPlr2());
        //     }
        //     // print current playe
        //     cout << G->getCurrentPlayer()->getUsername() << endl;
        //     cout << G->getCurrentPlayer()->getSymbol() << endl;
        // }
    } else {
        if (num == 1) {
            plr1 = new Player();
            plr1->setUsername(username);
            plr1->setWins(wins);
            plr1->setLoses(loses);
            plr1->setSymbol('X');
            AI->setPlr1(plr1);
        } else {
            plr2 = new Player();
            plr2->setUsername(username);
            plr2->setWins(wins);
            plr2->setLoses(loses);
            plr2->setSymbol('O');
            AI->setPlr2(plr2);
        }
    }
}

// EM_JS(void, updateWinnerAndLoser, (const char* winner, const char* loser), {
//     const openRequest = indexedDB.open("TicTacToe", 1);

//     let winnerUsername = UTF8ToString(winner);
//     let loserUsername = UTF8ToString(loser);

//     // Create the schema in the upgradeneeded event
//     openRequest.onupgradeneeded = function(e)
//     {
//         const db = e.target.result;
//         if (!db.objectStoreNames.contains("PlayerData"))
//         {
//             db.createObjectStore("PlayerData", {keyPath : 'username'});
//         }
//     };

//     openRequest.onerror = function(e)
//     {
//         console.error('Error opening database:', e.target.error);
//     };

//     openRequest.onsuccess = function(e)
//     {
//         const db = e.target.result;

//         // Create a transaction to write data
//         const transaction = db.transaction("PlayerData", 'readwrite');

//         // Get the object store from the transaction
//         const store = transaction.objectStore("PlayerData");

//         let d = store.get(u);
//     };
// });

void undoMoveCPP() {
    if (G->getIsCurrentRunning() == false) {
        EM_ASM({
            alert("Game Over, you have to go back to the main menu to start a new game");
        });
        return;
    }
    if (G->getCurrentPlayer()->getUndoCount() == 1) {
        EM_ASM({
            alert("You have already used your undo move");
        });
        return;
    }
    bool undo = G->getUndoStatus();
    if (undo == true) {
        return;
    }
    // G->getCurrentPlayer()->setUndoStatus(true);
    G->getCurrentPlayer()->setUndoCount(1);
    Mul->changeGameState();
    Mul->swapPlayer();
    // update the game state
    string symb = G->getCurrentPlayer()->getSymbol() == 'X' ? "X" : "O";
    EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerText = UTF8ToString($0)[i];
        }
        let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
        currentPlrHeading = UTF8ToString($1);
        console.log(UTF8ToString($2));
        document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(" + UTF8ToString($2) + ")";
    }, GameState::presState, G->getCurrentPlayer()->getUsername().c_str(), symb.c_str());
}

void movePlr(const char* cellID) {
    G->setUndoStatus(false);
    // check if current plr is plr1 or plr2, if plr1 then set element to X else O
    if (G->getCurrentPlayer()->getSymbol() == 'X' && G->getIsCurrentRunning() == true){
        // update prevState
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                G->getState().prevState[i][j] = G->getState().presState[i][j];
            }
        }
        int* checkMove = new int(0);
        EM_ASM_ARGS({
            let cell = document.getElementById(UTF8ToString($0));
            if (cell.innerHTML == "X" || cell.innerHTML == "O") {
                alert("Invalid Move, please try again");
            } else {
                cell.innerHTML = "X";
                updateJSState();
                setValue($1, 1, "i32");
            }
        }, cellID, checkMove);
        if (*checkMove == 0) {
            delete checkMove;
            return;
        }
        delete checkMove;
        string check = G->getCurrentPlayer()->checkWinner();
        if (check == "continue") {
            // EM_ASM({
            //     alert(UTF8ToString($0) + " wins");
            // }, G->getCurrentPlayer()->getUsername().c_str());
            // G->setIsCurrentRunning(false);
            G->setCurrentPlayer(Mul->getPlr2());
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(O)";
            }, G->getCurrentPlayer()->getUsername().c_str());
        } else if (check == "win") {
            // updateWinnerAndLoser(G->getCurrentPlayer()->getUsername().c_str(), Mul->get);
        }
    } else if (G->getCurrentPlayer()->getSymbol() == 'O' && G->getIsCurrentRunning() == true) {
        // update prevState
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                G->getState().prevState[i][j] = G->getState().presState[i][j];
            }
        }
        int* checkMove = new int(0);
        EM_ASM_ARGS({
            let cell = document.getElementById(UTF8ToString($0));
            if (cell.innerHTML == "X" || cell.innerHTML == "O") {
                alert("Invalid Move, please try again");
            } else {
                cell.innerHTML = "O";
                updateJSState();
                setValue($1, 1, "i32");
            }
        }, cellID, checkMove);
        if (*checkMove == 0) {
            delete checkMove;
            return;
        }
        delete checkMove;
        string check = G->getCurrentPlayer()->checkWinner();
        if (check == "continue") {
            // EM_ASM({
            //     alert(UTF8ToString($0) + " wins");
            // }, G->getCurrentPlayer()->getUsername().c_str());
            // G->setIsCurrentRunning(false);
            G->setCurrentPlayer(Mul->getPlr1());
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(X)";
            }, G->getCurrentPlayer()->getUsername().c_str());
        } else if (check == "win") {
            // updateWinnerAndLoser();
        }
    } else {
        cout << G->getIsCurrentRunning() << endl;
        cout << G->getCurrentPlayer()->getSymbol() << endl;
        EM_ASM({
            alert("Game Over, you have to go back to the main menu to start a new game");
        });
    }
}

void continueMulGame() {
    delete G;
    delete Mul;
    G = new Game();
    Mul = new Multiplayer();

    Mul->setPlr1(plr1);
    Mul->setPlr2(plr2);
    setCurrentPlrAtBegin();
    plr1->setUndoCount(0);
    plr2->setUndoCount(0);

    cout << "Game started" << endl;
    EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerHTML = "_";
        }
    });
}