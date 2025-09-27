#include "tic_tac_toe.h"

char **board;
int gameChoice;
int randInt1,randInt2;
int boardSize;
int askRole;
char player;
char players[3] = {'X','O','Z'};
int currentPlayerIndex = 0;
int totalPlayers;

int getRandomNumber(int *rand1,int *rand2,int size){

    // Generate Random numbers based on boardSize
    *rand1 = rand()%size;
    *rand2 = rand()%size;

    return 0;
    
}

void initializeBoard(){
    
    do{
        printf("Enter a board size: ");
        scanf("%d",&boardSize);
    }while (boardSize<3 || boardSize >10);
    
    
    //Allocate memory for board
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

    //Ask the player in which mode they want to play
    printf("\n------How do you want to play this Game------");
    printf("\n1. Press 1 for 2 players");
    printf("\n2. Press 2 to play against the computer");
    printf("\n3. Press 3 for 3 players\n");
    scanf("%d",&choiceNumber);

    return choiceNumber;



}

void displayBoard() {
    
    //print the numbers for top border
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

        //checks only if numbers are there
        if(scanf("%d %d", &row, &column) != 2){
            printf("\nPlease enter numbers only\n");
            //clears the buffer
            while (getchar() != '\n');
            continue;
        }

        if(row<0 || row >=boardSize||column<0||column>=boardSize||board[row][column] !=' '){
            printf("\n1. row and column must be between 1 and 2.");
            printf("\n2. Can select only empty cells\n\n");
            continue;
        }

        //assign the symbol to the correct row and column
        board[row][column] = player;

        break;

    }

    

}

void acceptComputerInput(){
    printf("\n---- Computers Turn -----\n");

    //checks if all blocks are occupied
    while (board[randInt1][randInt2] != ' ')
    {
        getRandomNumber(&randInt1,&randInt2,boardSize);   
    }
    
    board[randInt1][randInt2] = player;
    printf("---- Computer choose row = %d and column = %d ----\n\n",randInt1,randInt2);



}

void logResult(char status){
    //open a text file to append it
    FILE *f = fopen("game_log.txt","a");

    //check if file got a error
    if(f == NULL){
        printf("Error opening file\n");
        return;
    }
    
    //starts a time object
    time_t now = time(NULL);
    fprintf(f,"Date: %s",ctime(&now));

    if (status == 'D') {
        fprintf(f, "Result: Draw\n");
    }
    else if(status == 'M'){
        fprintf(f, "Move made by Player %c\n", player);

    }
    else {
        fprintf(f, "Winner: Player %c\n", status);
    }

    //prints the board to the file
    fprintf(f, "Board Size: %d\n", boardSize);
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            fprintf(f, "%c ", board[i][j]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "-------------------------\n\n");

    fclose(f);



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
            logResult(first);
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
            logResult(first);
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
            logResult(first);
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
            logResult(first);
            return true;
        }
    }

    return false;  // no win found
}


bool checkDraw(){
    //checks if all blocks are occupied
    for(int i = 0;i<boardSize;i++){
        for(int j = 0;j < boardSize;j++){
            if (board[i][j] == ' '){
                return false;
            }

    }

    }
    printf("\nGame has drawn\n");
    logResult('D');
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

    //asks for the Game mode
    if(gameChoice == 1){
        totalPlayers = 2;
    }
    else if(gameChoice ==2){
        totalPlayers = 2;
    }
    else if(gameChoice ==3){
        totalPlayers =3;
        askRoles();
    }

    //assigns the first player symbol
    player= players[currentPlayerIndex];
    displayBoard();

    while(true){
        if(gameChoice == 1){
            acceptUserInput();
        }
        else if(gameChoice == 2){
            if(player == 'X'){
                acceptUserInput();
            }
            else{
                acceptComputerInput();
            }
        }
        else if(gameChoice == 3){
            if(askRole == 1){
                if(player == 'X' || player == 'O'){
                    acceptUserInput();
                }
                else{
                    acceptComputerInput();
                }

            }
            else if(askRole == 2){
                if(player == 'X'){
                    acceptUserInput();
                }
                else{
                    acceptComputerInput();
                }
            }
        }

        logResult('M');

        displayBoard();


        //check for win and then draw
        if (checkWin()) break;
        if (checkDraw()) break;

        //changes player symbol every loop
        currentPlayerIndex = (currentPlayerIndex +1) %totalPlayers;
        player = players[currentPlayerIndex];
    }
    
    
    //free the allocated memory
    for (int i = 0; i < boardSize; i++) {
    free(board[i]);
    }
    free(board);

    return 0;

}

