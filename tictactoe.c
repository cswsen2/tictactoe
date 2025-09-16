#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *board;
char player = 'X';

void initializeBoard(){
    board = (char*)malloc(3*3*sizeof(char));

    for(int i =0; i<3;i++){
        for(int j = 0;j<3;j++){
            board[i*3+j]=' ';
        }
    }



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

        if (player == 'X'){
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
    displayBoard();

    while (true)
    {
        acceptUserInput();
        displayBoard();
        if (checkWin()) break;
        if (checkDraw()) break;


    }
    
    free(board);


    return 0;

}

