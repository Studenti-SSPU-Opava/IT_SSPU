#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            for (int j = 0; j < SIZE; j++) {
                printf("-");
                if (j < SIZE - 1) {
                    printf("+");
                }
            }
            printf("\n");
        }
    }
}

bool checkWin(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

int main() {
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char player = 'X';
    int row, col;
    bool win = false;
    for (int i = 0; i < SIZE * SIZE; i++) {
        printBoard(board);
        printf("Player %c, enter row and column: ", player);
        scanf("%d %d", &row, &col);
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
            printf("Invalid move\n");
            i--;
            continue;
        }
        board[row][col] = player;
        if (checkWin(board, player)) {
            win = true;
            break;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    printBoard(board);
    if (win) {
        printf("Player %c wins\n", player);
    } else {
        printf("It's a draw\n");
    }
    return 0;
}