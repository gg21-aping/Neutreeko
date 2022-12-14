#include "algo.h"
#include "board.h"
#include "hash.h"
#include "variable.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

char SELF;
char OPPONENT;

int count = 0;

void print_usage(char *executable) {
    fprintf(stderr, "Usage: %s [0, 1]\n", executable);
}

int main(int argc, char *argv[]) {
    printf("search level: %d\n", SEARCH_LEVEL);
    // initialize board
    char board[5][5] = {
        " O O ",
        "  X  ",
        "     ",
        "  O  ",
        " X X "};

    print_board(board);
    printf("Game Starts!\n");

    // check if the argument is valid
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }
    // player selection: 0-> user black / 1-> computer black
    int computer;
    if (!strcmp(argv[1], "0")) {
        computer = 0;
        SELF = 'O';
        OPPONENT = 'X';
        printf("You play BLACK.\n\n");
    } else if (!strcmp(argv[1], "1")) {
        computer = 1;
        SELF = 'X';
        OPPONENT = 'O';
        printf("You play WHITE.\n\n");
    } else {
        print_usage(argv[0]);
        return 1;
    }

    // Start game.
    int x, y, dir;
    int new_x, new_y;
    char move[10];

    while (1) {
        // Draw
        if (count == 300) {
            printf("Draw");
            break;
        }

        // if computer goes first
        if (computer) {
            count++;

#ifdef USE_HASH
            reset_used();
#endif
            printf("Running...\n\n");
            run(board, 0, &x, &y, &dir, MIN, MAX);
            // Re-write the board in-place.
            go_direction(board, board, x, y, dx[dir], dy[dir], &new_x, &new_y);
            printf("%c%c%c%c\n", '5' - x, 'A' + y, '5' - new_x, 'A' + new_y);
            print_board(board);
            if (board_value(board) == VALUE_WIN) {
                printf("You Lose\n");
                break;
            }
        }

        // read user move
        printf("Your turn. Enter your move:\n");
        // For debugging when using tee.
        fflush(stdout);
        while (1) {
            fgets(move, sizeof move, stdin);
            // check invalid move
            if (go_opponent(board, move)) {
                count++;
                break;
            }
            printf("Invalid move, please enter again:\n");
            // For debugging when using tee.
            fflush(stdout);
        }

        print_board(board);
        if (board_value(board) == VALUE_LOSE) {
            printf("You Win!\n");
            break;
        }
        computer = 1;
    }

    return 0;
}
