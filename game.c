//Used AI tool to help me with the understanding of the code.
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const unsigned long long RED_START =  0x00000000000FFF00ULL;
const unsigned long long RED_PROMOTION_MASK =  0xFF00000000000000ULL;
const unsigned long long BLACK_START = 0x00000FFF00000000ULL;
const unsigned long long BLACK_PROMOTION_MASK = 0x00000000000000FFULL;
const unsigned long long VALID_SQUARES = 0x55AA55AA55AA55AAULL;


int rc_to_index(int row, int column) {
    return (7 - row) * 8 + (7 - column);
}

void PrintBoard(const GameState *g){
    printf("Current turn: %s\n", g->current_turn == 0 ? "Red" : "Black");
    printf("  0 1 2 3 4 5 6 7\n");
    for (int row = 0; row < 8; row++){
        printf("%d ", row); //Added some spacing for better visuals of the board.
        for (int column = 0; column < 8; column++){
            int bit = rc_to_index(row, column);
            unsigned long long mask = 1ULL << bit;
            char character = ((VALID_SQUARES & mask) == 0) ? ' ' : '.';
            if (g->red_pieces & mask) character = 'r';
            if (g->red_kings & mask) character = 'R';
            if (g->black_pieces & mask) character = 'b';
            if (g->black_kings & mask) character = 'B';
            printf(" %c", character);
        }
        printf("\n");
    }
}

void InitGame(GameState *g){
    g->red_pieces = RED_START;
    g->red_kings = g->black_kings = 0ULL;
    g->black_pieces = BLACK_START;
    g->current_turn = 0; // Red starts
}

void CheckKingPromotion(GameState *g){
    g->black_kings |= g->black_pieces & BLACK_PROMOTION_MASK;
    g->red_kings |= g->red_pieces & RED_PROMOTION_MASK;
}

int CheckWin(const GameState *g){
    if ((g->black_pieces | g->black_kings) == 0) return 0; // Red wins
    if ((g->red_pieces | g->red_kings) == 0) return 1; // Black wins
    return -1; // No winner yet
}

int MovePiece(GameState *g, int r1, int c1, int r2, int c2){
    int from = rc_to_index(r1, c1);
    int to = rc_to_index(r2, c2);
    unsigned long long mask_from = 1ULL << from, mask_to = 1ULL << to;

    if (!(VALID_SQUARES & mask_to) || (mask_to & (g->red_pieces | g->black_pieces | g->red_kings | g->black_kings))){
printf("Improper move: The destination is not empty or not playable.\n");
        return 0;
    }

    //These set of lines are determing which is the player's piece.
    int isRedTurn = (g->current_turn == 0);
    int isBlackPiece = (g->black_pieces | g->black_kings) & mask_from;
    int isRedPiece = (g->red_pieces | g->red_kings) & mask_from;
    

    if ((isRedTurn && !isRedPiece) || (!isRedTurn && !isBlackPiece)){
        printf("Improper move: There is not piece placed at the location.\n");
        return 0;
    }

    int dr = r2 - r1, dc = abs(c2 - c1);
    if (dc != abs(dr) || (abs(dr) != 1 && abs(dr) != 2)){
        printf("Improper move: The move shape is invalid.\n");
        return 0;
    }

    if (abs(dr) == 2){
        int mr = (r1 + r2) / 2, mc = (c1 + c2) / 2;
        int mid = rc_to_index(mr, mc);
        unsigned long long mask_mid = 1ULL << mid;
        unsigned long long opponent_pieces = isRedTurn ? (g->black_pieces | g->black_kings) : (g->red_pieces | g->red_kings);
        if (!(opponent_pieces & mask_mid)){
            printf("Improper move: There is no opponent to catch.\n");
            return 0;
        }

        //These set of lines are directed to remvoing the opponent.
        g->red_pieces &= ~mask_mid;
        g->black_pieces &= ~mask_mid;
        g->red_kings &= ~mask_mid;
        g->black_kings &= ~mask_mid;
    
    }

    int wasKing = ((g->red_kings | g->black_kings) & mask_from) != 0;
    g->red_pieces &= ~mask_from;
    g->red_kings &= ~mask_from;
    g->black_pieces &= ~mask_from;
    g->black_kings &= ~mask_from;

    if(isRedTurn) g->red_pieces |= mask_to;
    else g->black_pieces |= mask_to;

    if (wasKing){
        if (isRedTurn) g->red_kings |= mask_to;
        else g->black_kings |= mask_to;
    
    }
    
    CheckKingPromotion(g);
    g->current_turn = 1 - g->current_turn; // Switch turns
    return 1;
}

void save_game(GameState *g, const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file){ printf("Save error.\n"); return; }
    fprintf(file, "red_pieces=0x%016I64X\nblack_pieces=0x%016I64X\n", g->red_pieces, g->black_pieces);
    fprintf(file, "red_kings=0x%016I64X\nblack_kings=0x%016I64X\ncurrent_turn=%d\n", g->red_kings, g->black_kings, g->current_turn);
    fclose(file);
    printf("Game is saved successfully.\n");
    }
    
void load_game(GameState *g, const char *filename){
        FILE *fp = fopen(filename, "r");
        if (!fp){ printf("Loading error.\n"); return; }
        fscanf(fp, "red_pieces=%I64x\n", &g->red_pieces);
        fscanf(fp, "black_pieces=%I64x\n", &g->black_pieces);
        fscanf(fp, "red_kings=%I64x\n", &g->red_kings);
        fscanf(fp, "black_kings=%I64x\n", &g->black_kings);
        fscanf(fp, "current_turn=%d\n", &g->current_turn);
        fclose(fp);
        printf("Game is loaded from %s\n", filename);
        }


void PlayGame(){
    GameState g; 
    InitGame(&g);
    char command[32], filename[64];
    int r1, c1, r2, c2;

    printf("Welcome to the game of checkers! The commands are: move r1 c1 r2 c2 | save file | load file | exit\n");
    
    while (1){
        PrintBoard(&g);
        int winner = CheckWin(&g);
        if (winner == 0) { printf("Red wins!\n"); break;  }
        if (winner == 1) { printf("Black wins!\n"); break;  }

        printf("> ");
        if (scanf("%s", command) != 1) break;

        if (strcmp(command, "move") == 0){
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
            MovePiece(&g, r1, c1, r2, c2);
        } else if (strcmp(command, "save") == 0){
            scanf("%s", filename);
            save_game(&g, filename);
        } else if (strcmp(command, "load") == 0){
            scanf("%s", filename);
            load_game(&g, filename);
        } else if(strcmp(command, "exit") == 0){
            printf("Thanks for playing!\n");
            break;
        } else {
            printf("Invalid command.\n");
        }
    }
}
