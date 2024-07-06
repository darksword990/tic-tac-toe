#ifndef GAME_FUNC
#define GAME_FUNC
#include <emscripten.h>

extern "C" {
    extern void updateWinnerAndLoser(const char*, const char*);
    extern void plrData(int, const char*, const char*);
    extern void updateJSState();
    extern void updateUserDataPowerup(const char*, const char*);
    extern void showGameStatus(const char*);
    EMSCRIPTEN_KEEPALIVE void LoginUser1(int, const char*, const char*);
    EMSCRIPTEN_KEEPALIVE void LoginUser2(int, const char*, const char*);
    EMSCRIPTEN_KEEPALIVE void setCurrentPlrAtBegin();
    EMSCRIPTEN_KEEPALIVE void setCurrentPlrAtBeginAI(int);
    EMSCRIPTEN_KEEPALIVE void updateGameState(const char*, int);
    EMSCRIPTEN_KEEPALIVE void setPlr(int, const char*);
    EMSCRIPTEN_KEEPALIVE void movePlr(const char*);
    EMSCRIPTEN_KEEPALIVE void undoMoveCPP();
    EMSCRIPTEN_KEEPALIVE void refreshData();
    EMSCRIPTEN_KEEPALIVE void continueMulGame();
    EMSCRIPTEN_KEEPALIVE void continueAIGame();
    EMSCRIPTEN_KEEPALIVE bool checkGameRunning();
    EMSCRIPTEN_KEEPALIVE void sendUsername(const char*, const char*);
    EMSCRIPTEN_KEEPALIVE void beforeReload();
}

#endif