// /* Declaration and initialization of the board */
// char board[3][3];
 
// /* Initializing all cells to EMPTY using nested loops */
// for (int r = 0; r < 3; r++)
//     for (int c = 0; c < 3; c++)
//         board[r][c] = ' ';
 
// /* Accessing a specific cell */
// board[0][0] = 'X';   /* Top-left corner  */
// board[1][1] = 'O';   /* Center cell      */
// board[2][2] = 'X';   /* Bottom-right     */
// /*
//  * Tic-Tac-Toe Game in C
//  * 2-Player Console Game using 2D Array
//  * Author  : Mayan Pathania
//  * Date    : 2026
//  * Language: C (C99 Standard)
//  */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Constants for board dimensions and player symbols
#define ROWS   3
#define COLS   3
#define EMPTY  ' '
#define P1     'X'
#define P2     'O'
 
// Global board variable
char board[ROWS][COLS];
 
// Functions
void  initBoard(void);
void  printBoard(void);
int   makeMove(char player, int row, int col);
int   checkWin(char player);
int   isBoardFull(void);
void  printResult(char winner);
void  getPlayerNames(char *name1, char *name2);
void  clearScreen(void);
int   validateInput(int row, int col);
void  printStats(int wins1, int wins2, int draws);
void  playGame(void);
 
// Main function: Entry point of the program
int main(void) {
    int  playAgain = 1;
    char choice[4];
 
    printf("\n================================================\n");
    printf("        TIC-TAC-TOE  -  2 Player Game          \n");
    printf("================================================\n");
 
    while (playAgain) {
        playGame();
        printf("\nPlay again? (yes/no): ");
        scanf("%3s", choice);
        if (strcmp(choice, "yes") != 0 && strcmp(choice, "y") != 0)
            playAgain = 0;
    }
    printf("\nThank you for playing! Goodbye.\n\n");
    return 0;
}
 
//initBoard: Fill board with EMPTY spaces  
void initBoard(void) {
    int r, c;
    for (r = 0; r < ROWS; r++)
        for (c = 0; c < COLS; c++)
            board[r][c] = EMPTY;
}
 
//printBoard: Render the 3x3 grid to console 
void printBoard(void) {
    int r, c;
    printf("\n     Col 1   Col 2   Col 3\n");
    printf("   +-------+-------+-------+\n");
    for (r = 0; r < ROWS; r++) {
        printf("Row%d", r + 1);
        for (c = 0; c < COLS; c++)
            printf(" |   %c   ", board[r][c]);
        printf(" |\n");
        printf("   +-------+-------+-------+\n");
    }
    printf("\n");
}
 
//makeMove: Place player's symbol if cell is empty, else show error
int makeMove(char player, int row, int col) {
    if (board[row][col] != EMPTY) {
        printf("  [!] Cell (%d,%d) is already taken! Try again.\n",
               row + 1, col + 1);
        return 0;
    }
    board[row][col] = player;
    return 1;
}
 
//checkWin: Return 1 if player has won, else 0
int checkWin(char player) {
    int r, c;
 
    /* Check all three rows */
    for (r = 0; r < ROWS; r++)
        if (board[r][0] == player &&
            board[r][1] == player &&
            board[r][2] == player)
            return 1;
 
    /* Check all three columns */
    for (c = 0; c < COLS; c++)
        if (board[0][c] == player &&
            board[1][c] == player &&
            board[2][c] == player)
            return 1;
 
    /* Check main diagonal (top-left to bottom-right) */
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
        return 1;
 
    /* Check anti-diagonal (top-right to bottom-left) */
    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
        return 1;
 
    return 0;   /* No winner yet */
}
 
//isBoardFull: Return 1 if no EMPTY cells, else 0
int isBoardFull(void) {
    int r, c;
    for (r = 0; r < ROWS; r++)
        for (c = 0; c < COLS; c++)
            if (board[r][c] == EMPTY)
                return 0;
    return 1;
}
 
//validateInput: Ensure row and column are within 1-3
int validateInput(int row, int col) {
    if (row < 1 || row > 3 || col < 1 || col > 3) {
        printf("  [!] Invalid input! Row and Column must be 1-3.\n");
        return 0;
    }
    return 1;
}
 
//getPlayerNames: Prompt users to enter their names
void getPlayerNames(char *name1, char *name2) {
    printf("\nEnter name for Player 1 (X): ");
    scanf("%29s", name1);
    printf("Enter name for Player 2 (O): ");
    scanf("%29s", name2);
}
 
//printResult: Display the winner or if it's a draw
void printResult(char winner) {
    if (winner == EMPTY)
        printf("\n  *** It's a DRAW! Well played! ***\n");
    else
        printf("\n  *** Player '%c' WINS! Congratulations! ***\n", winner);
}
 
//printStats: Show current scoreboard after each round
void printStats(int wins1, int wins2, int draws) {
    printf("\n=== SCOREBOARD ===========================\n");
    printf("  Player X Wins : %d\n", wins1);
    printf("  Player O Wins : %d\n", wins2);
    printf("  Draws         : %d\n", draws);
    printf("==========================================\n");
}
 
//playGame: Main game loop for a single round, handles turns and game flow
void playGame(void) {
    char name1[30], name2[30];
    char currentPlayer;
    int  row, col, moved, gameOver;
    int  wins1 = 0, wins2 = 0, draws = 0;
    int  roundsPlayed = 0;
    char playRound[4];
 
    getPlayerNames(name1, name2);
 
    do {
        initBoard();
        currentPlayer = P1;
        gameOver      = 0;
        roundsPlayed++;
 
        printf("\n--- Round %d ---\n", roundsPlayed);
 
        while (!gameOver) {
            printBoard();
 
            /* Determine whose turn */
            if (currentPlayer == P1)
                printf("  %s's turn (X) - Enter Row Col (1-3): ", name1);
            else
                printf("  %s's turn (O) - Enter Row Col (1-3): ", name2);
 
            /* Read and validate input */
            if (scanf("%d %d", &row, &col) != 2) {
                printf("  [!] Please enter two integers.\n");
                while (getchar() != '\n'); /* flush buffer */
                continue;
            }
 
            if (!validateInput(row, col)) continue;
 
            /* Attempt the move (0-indexed internally) */
            moved = makeMove(currentPlayer, row - 1, col - 1);
            if (!moved) continue;
 
            /* Check win condition */
            if (checkWin(currentPlayer)) {
                printBoard();
                printResult(currentPlayer);
                if (currentPlayer == P1) wins1++;
                else                     wins2++;
                gameOver = 1;
            } else if (isBoardFull()) {
                printBoard();
                printResult(EMPTY);
                draws++;
                gameOver = 1;
            } else {
                /* Switch player */
                currentPlayer = (currentPlayer == P1) ? P2 : P1;
            }
        }
 
        printStats(wins1, wins2, draws);
 
        printf("\nPlay another round? (yes/no): ");
        scanf("%3s", playRound);
 
    } while (strcmp(playRound, "yes") == 0 || strcmp(playRound, "y") == 0);
}
