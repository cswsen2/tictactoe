#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

char **board;
char player = 'X';
int gameChoice;
int randInt1,randInt2;
int boardSize;
int askRole;

int getRandomNumber(int *rand1,int *rand2,int size){

    *rand1 = rand()%size;
    *rand2 = rand()%size;

    
    // printf("\nRandom number: %d\n",randInt);
}

void initializeBoard(){
    printf("Enter a board size: ");
    scanf("%d",&boardSize);

    board = (char**)malloc(boardSize*sizeof(char*));

    for(int i =0; i<boardSize;i++){
        board[i] = (char*)malloc(boardSize*sizeof(char));
        for(int j = 0;j<boardSize;j++){
            board[i][j]=' ';
        }
    }



}

int gameMode(){
    int choiceNumber;

    printf("\n------How do you want to play this Game------");
    printf("\n1. Press 1 for 2 players");
    printf("\n2. Press 2 to play against the computer");
    printf("\n3. Press 3 for 3 players\n");
    scanf("%d",&choiceNumber);

    return choiceNumber;



}

void displayBoard() {
    
    printf("    ");
    for (int j = 0; j < boardSize; j++) {
        printf(" %d  ", j);
    }
    printf("\n");

    // Print top border
    printf("   ");
    for (int j = 0; j < boardSize; j++) {
        printf("----");
    }
    printf("-\n");

    // Print rows
    for (int i = 0; i < boardSize; i++) {
        printf("%2d |", i);  // Row number with alignment
        for (int j = 0; j < boardSize; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");

        // Print separator line after each row
        printf("   ");
        for (int j = 0; j < boardSize; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

void acceptUserInput(){
    int row,column;

    while(1){
        printf("----Player %c turn----",player);
        printf("\nEnter a row and column(0-%d)?: ",boardSize-1);

        if(scanf("%d %d", &row, &column) != 2){
            printf("\nPlease enter numbers only\n");
            while (getchar() != '\n');
            continue;
        }

        if(row<0 || row >boardSize||column<0||column>boardSize||board[row][column] !=' '){
            printf("\n1. row and column must be between 1 and 2.");
            printf("\n2. Can select only empty cells\n");
            continue;
        }

        board[row][column] = player;

        if (player == 'X' && gameChoice != 2){
                player = 'O';
                break;
            // printf("\nPlayer has changed to O\n");
        }
        else{
            player = 'X';
            break;
        }


    }

    

}

void acceptComputerInput(){
    printf("\n---- Computers Turn -----\n");
    while (board[randInt1][randInt2] != ' ')
    {
        getRandomNumber(&randInt1,&randInt2,boardSize);   
    }
    
    board[randInt1][randInt2] = 'O';
    printf("---- Computer choose row = %d and column = %d ----\n",randInt1,randInt2);



}

bool checkWin() {
    // Check rows
    for (int i = 0; i < boardSize; i++) {
        char first = board[i][0];  // first element in the row
        if (first == ' ') continue;          // skip empty rows
        bool win = true;
        for (int j = 1; j < boardSize; j++) {
            if (board[i][j] != first) {
                win = false;
                break;
            }
        }
        if (win) {
            printf("\nPlayer %c has won!\n", first);
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < boardSize; j++) {
        char first = board[0][j];  // first element in the column
        if (first == ' ') continue;
        bool win = true;
        for (int i = 1; i < boardSize; i++) {
            if (board[i][j] != first) {
                win = false;
                break;
            }
        }
        if (win) {
            printf("\nPlayer %c has won!\n", first);
            return true;
        }
    }

    // Check main diagonal
    char first = board[0][0];
    if (first != ' ') {
        bool win = true;
        for (int i = 1; i < boardSize; i++) {
            if (board[i][i] != first) {
                win = false;
                break;
            }
        }
        if (win) {
            printf("\nPlayer %c has won!\n", first);
            return true;
        }
    }

    // Check anti-diagonal
    first = board[0][boardSize - 1];
    if (first != ' ') {
        bool win = true;
        for (int i = 1; i < boardSize; i++) {
            if (board[i][boardSize - 1 - i] != first) {
                win = false;
                break;
            }
        }
        if (win) {
            printf("\nPlayer %c has won!\n", first);
            return true;
        }
    }

    return false;  // no win found
}


bool checkDraw(){
    for(int i = 0;i<boardSize;i++){
        for(int j = 0;j < boardSize;j++){
            if (board[i][j] == ' '){
                return false;
            }

    }

    }
    printf("\nGame has drawn\n");
    return true;

    
}

void askRoles(){
    printf("\n1. Press 1 for 2 Players and a Computer");
    printf("\n2. Press 2 for 1 player and 2 Computers\n");
    scanf("%d",&askRole);

    

}


int main(){
    srand((unsigned int)time(NULL));

    printf("    Welcome to Tic-Tac-Toe\n");
    printf("===============================\n\n");
    initializeBoard();

    gameChoice = gameMode();
    if(gameChoice == 1){
        displayBoard();

        while (true)
        {
            acceptUserInput();
            displayBoard();
            if (checkWin()) break;
            if (checkDraw()) break;


        }

    }
    else if (gameChoice == 2)
    {
        
        displayBoard();
        while(true){
            getRandomNumber(&randInt1,&randInt2,boardSize);
            acceptUserInput();
            displayBoard();
            if (checkWin()) break;
            if (checkDraw()) break;
            acceptComputerInput();
            displayBoard();
            if (checkWin()) break;
            if (checkDraw()) break;

            
        }
    }

    else if(gameChoice == 3){
        askRoles();
        if(askRole == 1){


        }
        else if(askRole == 2);
    }
    

    
    
    for (int i = 0; i < boardSize; i++) {
    free(board[i]);
    }
    free(board);

}

