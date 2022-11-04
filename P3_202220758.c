#include <stdio.h>
#include <stdlib.h>

#define X 6 //row
#define Y 8 //column
#define LAST_LAYER 6 // the last layer of the board
#define PLAYER1 1
#define PLAYER2 2

void player1_turn(int b[][Y]);
void player2_turn(int b[][Y]);
void display_board(void); //print first board(before start the game)
void play_game_board(int b[][Y]); //print the board after start the game
void initial(int b[][Y]); //before start game, player choose where to put the add block
int win(int b[][Y]); //check for the 4 stones in a row
int win_check(int sum); //show the win message

//global variable
int board[X][Y] = {0}; 
int arr[8] = {0}; //column_number count check
int turn = PLAYER1; //start with player 1
int column_number, layer = 0;

int main(void) {
    //game setting for add block
    initial(board);

    //game start
    while (!win(board)) { //before someone win
        if (turn == PLAYER1) { //player1
            player1_turn(board);
        }
        else { //player2
            player2_turn(board);
        }
    }
    
    return 0;
}

void player1_turn(int b[][Y]) {
    printf("P1's marker is O, P2's marker is @\n");
    printf("P1's turn, Enter the column number: ");
    scanf("%d", &column_number);
    layer = ++arr[column_number - 1]; //column_number count check
    if (layer > 6) {
        printf("ERROR: The column is full.\n");
        printf("P1's turn, Enter the column number: ");
        scanf("%d", &column_number);
        layer = ++arr[column_number - 1];
    }
    board[LAST_LAYER - layer][column_number - 1] = 1; //put the 'O' stone
    play_game_board(board); // show the board
    turn = PLAYER2; //player2's turn now
}

void player2_turn(int b[][Y]) {
    printf("P1's marker is O, P2's marker is @\n");
    printf("P2's turn, Enter the column number: ");
    scanf("%d", &column_number);
    layer = ++arr[column_number - 1];
    if (layer > 6) {
        printf("ERROR: The column is full.\n");
        printf("P2's turn, Enter the column number: ");
        scanf("%d", &column_number);
        layer = ++arr[column_number - 1];
    }
    board[LAST_LAYER - layer][column_number - 1] = 10;
    play_game_board(board);    
    turn = PLAYER1;
}

void display_board(void) {
    //prints number of column
    printf(" ");
    for (int i = 1; i <= Y; i++)
        printf(" %2d ", i);
    puts(""); //new line

    //prints board
    for (int i = 0; i <= X-1; i++) {
        printf(" ");
        for (int j = 0; j <= Y-1; j++) {
            printf("|___");
    }
    printf("|");
    printf("\n");

    }
}

int win(int b[][Y]) {
   int i, j, k;
   int sum = 0;
   int draw;

   //garo
    for (i = 5; i >= 0; i--) { //garo counting
        for (j = 0; j <= 4; j++) { //sero counting
            for (k = 0; k < 4; k++) { //stone counting
                sum += b[i][j + k];
            }
            win_check(sum);
            if (sum != 0 && sum != 1 && sum != 2 && sum != 3 && sum != 4 && sum != 10 && sum != 20 && sum != 30 && sum != 40) {
                draw++; //if not game over
            }
            sum = 0; // sum initialization(because I have to check each of case; garo, sero, daegak)
        }
    }

    // sero
    for (i = 0; i <= 7; i++) { //sero counting
        for (j = 5; j >= 3; j--) { //garo counting
            for (k = 0; k < 4; k++) { //stone counting
                sum += b[j - k][i];
            }
            win_check(sum);
            if (sum != 0 && sum != 1 && sum != 2 && sum != 3 && sum != 4 && sum != 10 && sum != 20 && sum != 30 && sum != 40) {
                draw++;
            }
            sum = 0;
        }
    }

    // daegak
    for (i = 5; i >= 3; i--) {
        for (j = 1; j <= 5; j++) {
            for (k = 0; k < 4; k++) {
                sum += b[i - k][j + k];
            }
            win_check(sum);
            if (sum != 0 && sum != 1 && sum != 2 && sum != 3 && sum != 4 && sum != 10 && sum != 20 && sum != 30 && sum != 40) {
                draw++;
            }
            sum = 0;
        }
    }

    // yeokdaegak
    for (i = 5; i >= 3; i--) {
        for (j = 7; j >= 3; j--) {
            for (k = 0; k < 4; k++) {
                sum += b[i - k][j - k];
            }
            win_check(sum);
            if (sum != 0 && sum != 1 && sum != 2 && sum != 3 && sum != 4 && sum != 10 && sum != 20 && sum != 30 && sum != 40) {
                draw++;
            }
            sum = 0;
        }
    }
    
    if (draw == (5 * X) + (3 * Y) + 15 + 15) { //all of the case to make four stones in a row
        printf("Game ended in a draw.\n");
        exit(EXIT_SUCCESS);
    }
}

int win_check(int sum) {
   if (sum == 4) {
      printf("P1 wins!\n");
      exit(EXIT_FAILURE);
   }
   else if (sum == 40) {
      printf("P2 wins!\n");
      exit(EXIT_FAILURE);
   }
   return 0; // draw
}

void play_game_board(int b[][Y]) {
    char ch;
    //prints number of column
    printf(" ");
    for (int i = 1; i <= Y; i++)
        printf(" %2d ", i);
    puts(""); //new line

    //prints board
    for (int i = 0; i <= X-1; i++) {
        printf(" ");
        for (int j = 0; j <= Y-1; j++) {
            if (b[i][j] == 1) {
                ch = 'O';
            }
            else if (b[i][j] == 10) {
                ch = '@';
            }
            else if (b[i][j] == 100) {
                ch = 'X';
            }
            else { 
                ch = '_';
            }
            printf("|_%c_", ch);
    }
    printf("|");
    printf("\n");

    }
}

void initial(int b[][Y]) {
    int add_block, layer = 0;
    char ch;
    do {
        printf("For initialization, add block: ");
        scanf("%d", &add_block);
        layer = ++arr[add_block - 1];
        board[LAST_LAYER - layer][add_block - 1] = 100; //put add block
        if (add_block - 1 == -1) {
            board[LAST_LAYER -layer][add_block -1] = 0; //after the initialization, add block put on the wrong position.
            board[LAST_LAYER][add_block - 1] = 0;
        }
        
        if (LAST_LAYER - layer == 0) printf("ERROR: The column is full.\n"); 
    } while (add_block != 0);

    printf("Game started.\n");
    printf("\n");

    play_game_board(board);
}