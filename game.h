#ifndef GAME_H
#define GAME_H


typedef struct { //These set of lines are meant for structuring purposes for the game.
    unsigned long long red_pieces;
    unsigned long long red_kings;
    unsigned long long black_pieces;
    unsigned long long black_kings;
    int current_turn; // 0 is for Red, 1 is for Black.
} GameState;

//These set of lines are vital functions that are used for the game to function properly.
void InitGame(GameState *g);
int CheckWin(const GameState *g);
void PrintBoard(const GameState *g);
int MovePiece(GameState *g, int r1, int c1, int r2, int c2);
void CheckKingPromotion(GameState *g);


//Tese set of lines are meant for saving the game or loading the game.
void save_game(GameState *g, const char *filename);
void load_game(GameState *g, const char *filename);

//This set of line is meant for the game loop.
void PlayGame();

#endif