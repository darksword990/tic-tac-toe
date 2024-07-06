#include <TicTacToeFunctions.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>
#include <Multiplayer.h>
#include <AIGame.h>
#include <Player.h>
#include <Game.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
using namespace std;
using json = nlohmann::json;

extern Game* G;
extern string chosen;
extern Player* plr1;
extern Player* plr2;
extern pthread_t countdownThread;

EM_JS(void, updateWinnerAndLoser, (const char* winner, const char* loser), {
    const openRequest = indexedDB.open("TicTacToe", 1);

    let winnerUser = UTF8ToString(winner);
    let loserUser = UTF8ToString(loser);
    let winnerJSON = JSON.parse(winnerUser);
    let loserJSON = JSON.parse(loserUser);

    console.log(winnerJSON);
    console.log(loserJSON);

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

        let winnerData = store.get(winnerJSON.username);
        let loserData = store.get(loserJSON.username);

        winnerData.onsuccess = function(e) {
            // Update the wins and loses
            if (winnerData.result == undefined) {
                return;
            }
            winnerData.result.currentWins = winnerJSON.wins;
            winnerData.result.coins = winnerData.result.coins + 10;
            const request = store.put(winnerData.result);
            console.log(winnerData.result);

            request.onerror = function(e)
            {
                console.error('Error storing data:', e.target.error);
            };

            request.onsuccess = function()
            {
                console.log('Data stored successfully!');
            };
        };

        loserData.onsuccess = function(e) {
            // Update the wins and loses
            if (loserData.result == undefined) {
                return;
            }
            loserData.result.currentLoses = loserJSON.loses;
            const request = store.put(loserData.result);
            console.log(loserData.result);

            request.onerror = function(e)
            {
                console.error('Error storing data:', e.target.error);
            };

            request.onsuccess = function()
            {
                console.log('Data stored successfully!');
            };
        };
    };
});

EM_JS(void, updateJSState, (), {
    // send the updated game state to C++ in string form
    let gridItems = document.querySelectorAll(".grid-container .grid-item");
    let str = "";
    for (let i = 0; i < gridItems.length; i++) {
        str += gridItems[i].innerText;
    }
    Module.ccall("updateGameState", null, ["string", "number"], [str, 3]);
});

EM_JS(void, showGameStatus, (const char* text), {
    let heading = document.getElementById("current-turn-heading");

    let originalText = heading.innerText;

    heading.textContent = UTF8ToString(text) || text;

    
    setTimeout(() => {
        heading.textContent = originalText;
    }, 1500);
});

EM_JS(void, plrData, (int num, const char *username, const char *password), {
    const openRequest = indexedDB.open("TicTacToe", 1);

    let u = UTF8ToString(username).trim().replace(/[ ]+/g, "");
    let p = UTF8ToString(password).trim();
    console.log(u);
    console.log(p);

    if (u.length == 0) {
        alert("Username cannot be empty");
        return;
    }
    if (p.length == 0) {
        alert("Password cannot be empty");
        return;
    }

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
                let jsData = JSON.stringify(d.result);
                // Module.ccall("setPlr", null, [ "number", "string", "string", "number", "number", "number" ], [ num, UTF8ToString(indicator), d.result.username, d.result.currentWins, d.result.currentLoses, d.result.coins, d.result.purchasedUndo ]);
                Module.ccall("setPlr", null, ["number", "string"], [num, jsData]);
            }
            else
            {
                let usrData = {
                    username : u,
                    password : p,
                    currentWins : 0,
                    currentLoses : 0,
                    coins : 0,
                    purchasedUndo : false
                };

                const request = store.put(usrData);

                request.onerror = function(e)
                {
                    console.error('Error storing data:', e.target.error);
                };

                request.onsuccess = function()
                {
                    alert("Sign up successful!");
                    console.log('Data stored successfully!');
                    document.getElementById(`player${num}-login`).style.visibility = "hidden";
                    let jsData = JSON.stringify(usrData);
                    // Module.ccall("setPlr", null, [ "number", "string", "string", "number", "number", "number", "number" ], [ num, UTF8ToString(indicator), u, 0, 0, 0, usrData.purchasedUndo ]);
                    Module.ccall("setPlr", null, ["number", "string"], [num, jsData]);
                };
            };
        }
    };
});

EM_JS(void, updateUserDataPowerup, (const char* username, const char* typeOfPurchase), {
    const openRequest = indexedDB.open("TicTacToe", 1);

    let usernameJS = UTF8ToString(username);
    let typeOfPurchaseJS = UTF8ToString(typeOfPurchase);

    console.log(usernameJS);

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

        let userData = store.get(usernameJS);

        userData.onsuccess = function(e) {
            if (userData.result == undefined) {
                alert("Username does not exist")
            } else {
                if (typeOfPurchaseJS == "undo") {
                    if (userData.result.purchasedUndo) {
                        alert("Already purchased");
                        return;
                    }
                    if (userData.result.coins >= 100) {
                        userData.result.purchasedUndo = true;
                        userData.result.coins -= 100;
                        const request = store.put(userData.result);
                        request.onsuccess = function() {
                            alert("Successfully bought");
                            console.log("Data for undo saved");
                        }
                    } else {
                        alert("Insufficient funds");
                    }
                }
            }
            console.log(userData.result);
        };
    };
});

void refreshData() {
    G = nullptr;
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

void LoginUser1(int num, const char* username, const char* password) {
    plrData(num, username, password);
}

void LoginUser2(int num, const char* username, const char* password) {
    plrData(num, username, password);
}

void* countdown(void* arg) {
    int time = 60; // Time in seconds
    while (time >= 0) {
        if (checkGameRunning() == false || G == nullptr) {
            break;
        }
        MAIN_THREAD_EM_ASM({
            let timer = document.getElementById("current-ttt-time");
            timer.innerText = `${Math.floor($0/60)}m ${$0 % 60}s`;
        }, time);
        --time;
        sleep(1);
    }
    if (time < 0) {
        if (chosen == "multiplayer") {
            MAIN_THREAD_EM_ASM({
                let heading = document.getElementById("current-turn-heading");

                let originalText = heading.innerText;

                heading.textContent = "Time's up! Game draw!";
                setTimeout(() => {
                    heading.textContent = originalText;
                }, 1500);
                document.getElementById('cont-mul').style.visibility = "visible";
            });
        } else {
            MAIN_THREAD_EM_ASM({
                let heading = document.getElementById("current-turn-heading");

                let originalText = heading.innerText;

                heading.textContent = "Time's up! Game draw!";
                setTimeout(() => {
                    heading.textContent = originalText;
                }, 1500);
                document.getElementById('cont-ai').style.visibility = "visible";
            });
        }
    }
    if (G != nullptr) {
        G->setIsCurrentRunning(false);
    }
    return nullptr;
}

void setCurrentPlrAtBegin() {
        int random = rand() % 2 + 1;
        if (random == 1) {
            G = plr1; // polymorphism, tracking current player
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(X)";
            }, G->getUsername().c_str());
        } else {
            G = plr2;
            EM_ASM({
                let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                currentPlrHeading = UTF8ToString($0);
                console.log(currentPlrHeading);
                document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(O)";
            }, G->getUsername().c_str());
        }
        cout << G->getUsername() << endl;
        cout << G->getSymbol() << endl;
        plr1->setIsCurrentRunning(true);
    // }
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
        EM_ASM({
            let jsonStr = UTF8ToString($0);
            let json = JSON.parse(jsonStr);
            document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
            document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
            document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
            document.getElementById("x-wins").innerHTML = json.plr1.wins;
            document.getElementById("x-loses").innerHTML = json.plr1.loses;
            document.getElementById("x-coins").innerHTML = json.plr1.coins;
            document.getElementById("plr-2-counter-wins").innerHTML = json.plr2.username;
            document.getElementById("plr-2-counter-loses").innerHTML = json.plr2.username;
            document.getElementById("plr-2-coins").innerHTML = json.plr2.username;
            document.getElementById("o-wins").innerHTML = json.plr2.wins;
            document.getElementById("o-loses").innerHTML = json.plr2.loses;
            document.getElementById("o-coins").innerHTML = json.plr2.coins;
        }, jsonStr.c_str());
        if ((pthread_create(&countdownThread, nullptr, countdown, nullptr)) != 0) {
            cout << "Error creating thread" << endl;
            return;
        }
        pthread_detach(countdownThread);
}

void setCurrentPlrAtBeginAI(int difficulty) {
    plr2->setDifficulty(difficulty);
    cout << difficulty << endl;
    cout << plr1->getDifficulty() << endl;
    cout << plr2->getDifficulty() << endl;
    plr2->setUsername("AI");
    plr2->setSymbol('O');
    G = plr1;
    EM_ASM({
        let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
        currentPlrHeading = UTF8ToString($0);
        document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(X)";
    }, G->getUsername().c_str());
    G->setIsCurrentRunning(true);
    json j;
    j["plr1"] = {
        {"username", plr1->getUsername()},
        {"wins", plr1->getWins()},
        {"loses", plr1->getLoses()},
        {"coins", plr1->getCoins()}
    };
    j["plr2"] = {
        {"wins", plr2->getWins()},
        {"loses", plr2->getLoses()},
    };
    string jsonStr = j.dump(4);
    EM_ASM({
        let jsonStr = UTF8ToString($0);
        let json = JSON.parse(jsonStr);
        document.getElementById("plr-1-counter-wins").innerHTML = json.plr1.username;
        document.getElementById("plr-1-counter-loses").innerHTML = json.plr1.username;
        document.getElementById("plr-1-coins").innerHTML = json.plr1.username;
        document.getElementById("x-wins").innerHTML = json.plr1.wins;
        document.getElementById("x-loses").innerHTML = json.plr1.loses;
        document.getElementById("x-coins").innerHTML = json.plr1.coins;
        document.getElementById("ai-wins").innerHTML = json.plr2.wins;
        document.getElementById("ai-loses").innerHTML = json.plr2.loses;
    }, jsonStr.c_str());
    if ((pthread_create(&countdownThread, nullptr, countdown, nullptr)) != 0) {
            cout << "Error creating thread" << endl;
            return;
        }
        pthread_detach(countdownThread);
}

void updateGameState(const char* str, int size) {
    // Reconstruct the 2D array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // arr[i*size + j] calculates 2D index from 1D index
            plr1->getState().presState[i][j] = str[i*size + j];
        }
    }
}

// void setPlr(int num, const char* indicator, const char* username, int wins, int loses, int coins, bool purchasedUndo) {
void setPlr(int num, const char* data) {
    if (plr1 == nullptr) {
        plr1 = new Player();
    }
    if (plr2 == nullptr) {
        plr2 = new Player();
    }
    string strFromData = data;
    // string ind = indicator;
    json obj = json::parse(strFromData);
    if (chosen == "multiplayer") { // 2 for Multiplayer, 1 for AI
        if (num == 1) { // 1 for plr1, 2 for plr2
            plr1->setUsername(obj["username"]);
            plr1->setWins(obj["currentWins"]);
            plr1->setLoses(obj["currentLoses"]);
            plr1->setSymbol('X');
            plr1->setCoins(obj["coins"]);
            if (obj["purchasedUndo"] == true) {
                plr1->setPowerups("undo");
            }
        } else {
            plr2->setUsername(obj["username"]);
            plr2->setWins(obj["currentWins"]);
            plr2->setLoses(obj["currentLoses"]);
            plr2->setSymbol('O');
            plr2->setCoins(obj["coins"]);
            if (obj["purchasedUndo"] == true) {
                plr2->setPowerups("undo");
            }
        }
    } else {
        if (num == 1) {
            plr1->setUsername(obj["username"]);
            plr1->setWins(obj["currentWins"]);
            plr1->setLoses(obj["currentLoses"]);
            plr1->setSymbol('X');
            plr1->setCoins(obj["coins"]);
            if (obj["purchasedUndo"] == true) {
                plr1->setPowerups("undo");
            }
        }
    }
}

void undoMoveCPP()
{
    if (G == plr1)
    {
            if (plr2->getIsCurrentRunning() == false)
            {
                const char* status = "Game Over, you have to go back to the main menu to start a new game or click continue";
                showGameStatus(status);
                return;
            }
            if (plr2->getPowerups().twoUndoMoves == true) {
                if (plr2->getUndoCount() == 2)
                {
                    const char* status = "You have already used your undo move";
                    showGameStatus(status);
                    return;
                }
            } else {
                if (plr2->getUndoCount() == 1)
                {
                    const char* status = "You have already used your undo move";
                    showGameStatus(status);
                    return;
                }
            }
            bool undo = plr2->Multiplayer::getUndoStatus();
            cout << "Undo status : "<< undo << endl;
            if (undo == true)
            {
                return;
            }
            plr2->Multiplayer::setUndoStatus(true);
            plr2->setUndoCount(plr2->getUndoCount() + 1);
            plr2->changeGameState();
            plr2->swapPlayer();
            // update the game state
            string symb = plr2->getSymbol() == 'X' ? "X" : "O";
            EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerText = UTF8ToString($0)[i];
        }
        let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
        currentPlrHeading = UTF8ToString($1);
        console.log(UTF8ToString($2));
        document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(" + UTF8ToString($2) + ")"; }, G->getState().presState, plr2->getUsername().c_str(), symb.c_str());
        
    }
    else
    {
        
            if (plr1->getIsCurrentRunning() == false)
            {
                const char* status = "Game Over, you have to go back to the main menu to start a new game or click continue";
                showGameStatus(status);
                return;
            }
            if (plr1->getPowerups().twoUndoMoves == true) {
                if (plr1->getUndoCount() == 2)
                {
                    const char* status = "You have already used your undo move";
                    showGameStatus(status);
                    return;
                }
            } else {
                if (plr1->getUndoCount() == 1) {
                    const char* status = "You have already used your undo move";
                    showGameStatus(status);
                    return;
                }
            }
            bool undo = plr1->Multiplayer::getUndoStatus();
            cout << "undo status" << undo << endl;
            if (undo == true)
            {
                return;
            }
            plr1->Multiplayer::setUndoStatus(true);
            plr1->setUndoCount(plr1->getUndoCount() + 1);
            plr1->changeGameState();
            plr1->swapPlayer();
            // update the game state
            string symb = plr1->getSymbol() == 'X' ? "X" : "O";
            EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerText = UTF8ToString($0)[i];
        }
        let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
        currentPlrHeading = UTF8ToString($1);
        console.log(UTF8ToString($2));
        document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(" + UTF8ToString($2) + ")"; }, G->getState().presState, plr1->getUsername().c_str(), symb.c_str());
    }
}

void sendUsername(const char* username, const char* typeOfPurchase) {
    updateUserDataPowerup(username, typeOfPurchase);
}

void movePlr(const char* cellID) {
    // string ind = indicator;
    if (chosen == "multiplayer") {
        // check if current plr is plr1 or plr2, if plr1 then set element to X else O
        if (G->getSymbol() == 'X' && G->getIsCurrentRunning() == true){
            // Move
            const char* status = "Invalid Move, please try again";
            int* checkMove = new int(0);
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                if (cell.innerHTML == "X" || cell.innerHTML == "O") {
                    showGameStatus($2);
                } else {
                    setValue($1, 1, "i32"); // Emscripten function, in-built
                }
            }, cellID, checkMove, status);
            if (*checkMove == 0) {
                delete checkMove;
                return;
            }
            delete checkMove;
            // Previous moves
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    G->getState().prevState[i][j] = G->getState().presState[i][j];
                }
            }
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                cell.innerHTML = "X";
                updateJSState();
            }, cellID);
            plr1->Multiplayer::setUndoStatus(false);
            string check = G->checkWinner();
            if (check == "continue") {
                G = plr2;
                EM_ASM({
                    let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                    currentPlrHeading = UTF8ToString($0);
                    document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(O)";
                }, G->getUsername().c_str());
            }
        } else if (G->getSymbol() == 'O' && G->getIsCurrentRunning() == true) {
            const char* status = "Invalid Move, please try again";
            int* checkMove = new int(0);
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                if (cell.innerHTML == "X" || cell.innerHTML == "O") {
                    showGameStatus($2);
                } else {
                    setValue($1, 1, "i32");
                }
            }, cellID, checkMove, status);
            if (*checkMove == 0) {
                delete checkMove;
                return;
            }
            delete checkMove;
            // update prevState
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    G->getState().prevState[i][j] = G->getState().presState[i][j];
                }
            }
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                cell.innerHTML = "O";
                updateJSState();
            }, cellID);
            plr1->Multiplayer::setUndoStatus(false);
            string check = G->checkWinner();
            if (check == "continue") {
                G = plr1;
                EM_ASM({
                    let currentPlrHeading = document.getElementById("current-turn-heading").innerText;
                    currentPlrHeading = UTF8ToString($0);
                    document.getElementById("current-turn-heading").innerText = currentPlrHeading + "'s Turn " + "(X)";
                }, G->getUsername().c_str());
            }
        } else {
            cout << G->getIsCurrentRunning() << endl;
            cout << G->getSymbol() << endl;
            const char* status = "Game Over, you can either continue a new game or go back to the main menu";
            showGameStatus(status);
        }
    } else { // AI implementation
        if (G->getSymbol() == 'X' && G->getIsCurrentRunning() == true) {
            int* checkMove = new int(0);
            const char* status = "Invalid Move, please try again";
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                if (cell.innerHTML == "X" || cell.innerHTML == "O") {
                    showGameStatus($2);
                } else {
                    setValue($1, 1, "i32");
                }
            }, cellID, checkMove, status);
            if (*checkMove == 0) {
                delete checkMove;
                return;
            }
            delete checkMove;
            EM_ASM({
                let cell = document.getElementById(UTF8ToString($0));
                cell.innerHTML = "X";
                updateJSState();
            }, cellID);
            string check = G->checkWinner();
            if (check == "continue") {
                G = plr2;
                // AI Implementation
                AINextMove bestMove = plr2->findAIBestNextMove();
                int twoDIndex = bestMove.x * 3 + bestMove.y;
                EM_ASM_ARGS({
                    let cell = document.getElementById(`${$0}`);
                    cell.innerHTML = "O";
                    updateJSState();
                }, twoDIndex);
                // plr2->AIGame::setUndoStatus(false);
                string check = G->checkWinner();
                if (check == "continue") {
                    G = plr1;
                }
            }
        } else {
            cout << G->getIsCurrentRunning() << endl;
            cout << G->getSymbol() << endl;
            const char* status = "Game Over, you can either continue a new game or go back to the main menu";
            showGameStatus(status);
        }
    }
}

bool checkGameRunning() {
    if (G->getIsCurrentRunning() == false) {
        return false;
    } else {
        return true;
    }
}

void continueMulGame() {
    G = nullptr;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            plr2->getState().presState[i][j] = '_';
            plr1->getState().prevState[i][j] = '_';
        }
    }
    setCurrentPlrAtBegin();
    plr1->setUndoCount(0);
    plr2->setUndoCount(0);
    plr2->Multiplayer::setUndoStatus(true);

    cout << "Game started" << endl;
    EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerHTML = "_";
        }
    });
}

void beforeReload() {
    if (plr1 != nullptr) {
        delete plr1;
        cout << "Player 1 deleted" << endl;
        plr1 = nullptr;
    }
    if (plr2 != nullptr) {
        delete plr2;
        cout << "Player 2 deleted" << endl;
        plr2 = nullptr;
    }
    cout << "before reload called" << endl;
}

void continueAIGame() {
    G = nullptr;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            plr2->getState().presState[i][j] = '_';
            plr1->getState().prevState[i][j] = '_';
        }
    }
    setCurrentPlrAtBeginAI(plr2->getDifficulty());
    plr2->getDifficulty();
    plr1->setUndoCount(0);

    cout << "Game started" << endl;
    EM_ASM({
        let gridItems = document.querySelectorAll(".grid-container .grid-item");
        for (let i = 0; i < gridItems.length; i++) {
            gridItems[i].innerHTML = "_";
        }
    });
}