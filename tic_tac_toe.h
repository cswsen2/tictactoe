#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// Global variables
extern char **board;
extern int boardSize;
extern char player;
extern char players[3];
extern int currentPlayerIndex;
extern int totalPlayers;
extern int gameChoice;
extern int randInt1, randInt2;
extern int askRole;

// Function declarations
int getRandomNumber(int *rand1, int *rand2, int size);
void initializeBoard();
int gameMode();
void displayBoard();
void acceptUserInput();
void acceptComputerInput();
void logResult(char status);
bool checkWin();
bool checkDraw();
void askRoles();


#endif
