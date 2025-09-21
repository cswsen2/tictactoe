#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

char *board;
char player = 'X';
int gameChoice;
int randInt1,randInt2;

int getRandomNumber(int *rand1,int *rand2){
    srand((unsigned int)time(NULL));

    *rand1 = rand()%3;
    *rand2 = rand()%3;

    
    // printf("\nRandom number: %d\n",randInt);
}

void initializeBoard(){
    board = (char*)malloc(3*3*sizeof(char));

    for(int i =0; i<3;i++){
        for(int j = 0;j<3;j++){
            board[i*3+j]=' ';
        }
    }



}

int gameMode(){
    int choiceNumber;

    printf("\nHow do you want to play this Game");
    printf("\nPress 1 for 2 players");
    printf("\nPress 2 to play against the computer");
    printf("\nPress 3 for 3 players\n");
    scanf("%d",&choiceNumber);

    return choiceNumber;



}

void displayBoard() {
    
    printf("    0   1   2\n");
    printf("  -------------\n");

    for (int i = 0; i < 3; i++) {
        printf("%d|", i);

        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i*3 + j]);
            if (j < 2) printf("|");
        }
        printf("|\n");

        if (i < 2) {
            printf("  ---|---|---|---\n");
        }
    }
    printf("  -------------\n");
}

void acceptUserInput(){
    int row,column;

    while(1){
        printf("Enter a row and column(0-2)?: ");

        if(scanf("%d %d", &row, &column) != 2){
            printf("\nPlease enter numbers only\n");
            while (getchar() != '\n');
            continue;
        }

        if(row<0 || row >2||column<0||column>2||board[row*3+column] !=' '){
            printf("\n1. row and column must be between 1 and 2.");
            printf("\n2. Can select only empty cells\n");
            continue;
        }

        board[row*3+column] = player;

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
    printf("\nComputers Turn\n");
    while (board[randInt1*3+randInt2] != ' ')
    {
        getRandomNumber(&randInt1,&randInt2);   
    }
    
    board[randInt1*3+randInt2] = 'O';



}

bool checkWin(){
    int winPatterns[8][3] = {
        {0, 1, 2},  
        {3, 4, 5},  
        {6, 7, 8},  
        {0, 3, 6},  
        {1, 4, 7},  
        {2, 5, 8},  
        {0, 4, 8},  
        {2, 4, 6}   
    };

    // Loop over each possible win pattern
    for (int i = 0; i < 8; i++) {
        int a = winPatterns[i][0];
        int b = winPatterns[i][1];
        int c = winPatterns[i][2];

        
        if (board[a] != ' ' && board[a] == board[b] && board[b] == board[c]) {
            printf("\nPlayer %c has won!\n", board[a]);
            return true;  // Found a winner
        }
    }
    return false;  // No win found


}

bool checkDraw(){
    for(int i = 0;i<9;i++){
        if (board[i] == ' '){
            return false;
        }

    }
    printf("\nGame has drawn\n");
    return true;

    
}


int main(){

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
            getRandomNumber(&randInt1,&randInt2);
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
    

    
    
    free(board);


    return 0;

}

