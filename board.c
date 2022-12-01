#include "board.h"
#include "variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_board(char board[][5]) {
    printf("    A   B   C   D   E\n");
    printf("  +---+---+---+---+---+\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", 5 - i);
        for (int j = 0; j < 5; ++j) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        printf("  +---+---+---+---+---+\n");
    }
    printf("\n");
}

int in_bound(int x, int y) {
    return 0 <= x && x < 5 && 0 <= y && y < 5;
}

int board_value(char board[][5]) {
    // Shadowed the global variable...
    int dx[] = {0, 1, 1, -1};
    int dy[] = {1, 0, 1, 1};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == EMPTY) {
                continue;
            }
            for (int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                int n2x = i + dx[k] * 2;
                int n2y = j + dy[k] * 2;
                if (in_bound(nx, ny) && in_bound(n2x, n2y) &&
                    board[i][j] == board[nx][ny] && board[i][j] == board[n2x][n2y]) {
                    return board[i][j] == SELF ? VALUE_WIN : VALUE_LOSE;
                }
            }
        }
    }
    return 0;
}

int go_direction(char board[][5], char board_next[][5], int x, int y, int dx, int dy, int *new_x, int *new_y) {
    if (board[x][y] == EMPTY) {
        return 0;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board_next[i][j] = board[i][j];
        }
    }

    int nx, ny;
    int steps = 0;
    while (1) {
        nx = x + dx;
        ny = y + dy;
        if (in_bound(nx, ny) && board_next[nx][ny] == EMPTY) {
            board_next[nx][ny] = board_next[x][y];
            board_next[x][y] = EMPTY;
            *new_x = x = nx;
            *new_y = y = ny;
            ++steps;
        } else {
            break;
        }
    }
    return steps > 0;
}

int go_opponent(char board[][5], char *cmd) {
    int sx = 4 - (cmd[0] - '1'), sy = cmd[1] - 'A';
    int ex = 4 - (cmd[2] - '1'), ey = cmd[3] - 'A';
    // Simple sanity check.
    if (!in_bound(sx, sy) || !in_bound(ex, ey)) {
        return 0;
    }
    if (board[sx][sy] != OPPONENT) {
        return 0;
    }

    // Make sure it's in the 8 valid directions and the path is clear.
    int dir_x = ex == sx ? 0 : (ex - sx) / abs(ex - sx);
    int dir_y = ey == sy ? 0 : (ey - sy) / abs(ey - sy);
    int x = sx, y = sy;
    while (in_bound(x, y) && (x != ex || y != ey)) {
        x += dir_x;
        y += dir_y;
        if (board[x][y] != EMPTY) {
            return 0;
        }
    }

    // Make sure it hits the border or another chess.
    x += dir_x;
    y += dir_y;
    if (in_bound(x, y) && board[x][y] == EMPTY) {
        return 0;
    }

    // Make the move finally.
    board[sx][sy] = EMPTY;
    board[ex][ey] = OPPONENT;
    return 1;
}