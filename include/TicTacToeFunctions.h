#ifndef GAME_FUNC
#define GAME_FUNC
#include <emscripten.h>

class Player;

extern "C" {
    extern void plrData(int, const char*, const char*, const char*);
    extern void updateJSState();
    EMSCRIPTEN_KEEPALIVE void LoginUser1(int, const char*, const char*, const char*);
    EMSCRIPTEN_KEEPALIVE void LoginUser2(int, const char*, const char*, const char*);
    EMSCRIPTEN_KEEPALIVE void setCurrentPlrAtBegin();
    EMSCRIPTEN_KEEPALIVE void setCurrentPlr(Player*);
    EMSCRIPTEN_KEEPALIVE void updateGameState(const char*, int, int);
    EMSCRIPTEN_KEEPALIVE void setPlr(int, const char*, const char*, int, int);
    EMSCRIPTEN_KEEPALIVE void movePlr(const char*);
    EMSCRIPTEN_KEEPALIVE void undoMoveCPP();
    EMSCRIPTEN_KEEPALIVE void refreshData();
    EMSCRIPTEN_KEEPALIVE void continueMulGame();
}

#endif