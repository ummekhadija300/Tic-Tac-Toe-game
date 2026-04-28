#include <stdio.h>
#define ROWS 3
#define COLS 3
typedef struct {
    char name[20];
    char symbol;
} Player;
void drawBoard(char board[ROWS][COLS]) {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}
int checkWin(char board[ROWS][COLS], char symbol) {
    int i;
    for (i = 0; i < ROWS; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return 1;
        }
    }
    for (i = 0; i < COLS; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return 1;
        }
    }
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
        return 1;
    }
    return 0;
}
void saveGame(char board[ROWS][COLS], char filename[]) {
    int i,j;
	FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fprintf(file, "%c ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Game saved to %s!\n", filename);
}
void loadGame(char board[ROWS][COLS], char filename[]) {
    int i,j;
	FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for ( i = 0; i < ROWS; i++) {
        for ( j = 0; j < COLS; j++) {
            fscanf(file, " %c", &board[i][j]);
        }
    }
    fclose(file);
    printf("Game loaded from %s!\n", filename);
}
int main() {
    char board[ROWS][COLS] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    Player players[2];
    int currentPlayer = 0;
    int gameResult = 0;

    printf("Enter Player 1 Name: ");
    scanf("%s", players[0].name);
    players[0].symbol = 'X';

    printf("Enter Player 2 Name: ");
    scanf("%s", players[1].name);
    players[1].symbol = 'O';
    printf("Do you want to load a saved game? (y/n): ");
    char loadChoice;
    scanf(" %c", &loadChoice);
    if (loadChoice == 'y') {
        printf("Enter filename: ");
        char filename[50];
        scanf("%s", filename);
        loadGame(board, filename);
    } 
        while (gameResult == 0) {
            drawBoard(board);
            if (currentPlayer == 0) {
                printf("%s's turn (%c)\n", players[0].name, players[0].symbol);
            } else {
                printf("%s's turn (%c)\n", players[1].name, players[1].symbol);
            }
            int move;
            printf("Enter your move (1-9): ");
            scanf("%d", &move);

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (board[row][col] != 'X' && board[row][col] != 'O') {
                if (currentPlayer == 0) {
                    board[row][col] = players[0].symbol;
                } else {
                    board[row][col] = players[1].symbol;
                }

                if (checkWin(board, players[0].symbol)) {
                    drawBoard(board);
                    printf("%s wins!\n", players[0].name);
                    gameResult = 1;
                } else if (checkWin(board, players[1].symbol)) {
                   drawBoard(board);
                    printf("%s wins!\n", players[1].name);
                    gameResult = 1;
                }
                currentPlayer = 1 - currentPlayer;
            } else {
                printf("Invalid move! Try again.\n");
            }
        }
        printf("Do you want to save the game? (y/n): ");
        char saveChoice;
        scanf(" %c", &saveChoice);
        if (saveChoice == 'y') {
            printf("Enter filename: ");
            char filename[50];
            scanf("%s", filename);
            saveGame(board, filename);
        }
        return 0;
    }
