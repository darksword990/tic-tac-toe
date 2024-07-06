struct GameState {
    static char prevState[3][3];
    static char presState[3][3];
};

struct AINextMove {
    int x, y;
};

struct PowerupPurchases {
    bool twoUndoMoves;
};