#include <Player.h>
#include <iostream>
#include <pthread.h>
#include <emscripten.h>

using namespace std;

string chosen;
Game* G = nullptr;
Player* plr1 = nullptr;
Player* plr2 = nullptr;
pthread_t countdownThread;

extern "C" {
  EMSCRIPTEN_KEEPALIVE void multiplayerChosen() { // only createMultiplayer and createAIGame are called from JS
      chosen = "multiplayer";
      cout << "Multiplayer chosen" << endl;
  }

  EMSCRIPTEN_KEEPALIVE void AIGameChosen() {
      chosen = "ai";
      cout << "AI Game chosen" << endl;
  }
}