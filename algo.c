#include "algo.h"
#include "board.h"
#include "hash.h"
#include "variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run(char board[][5], int depth, int *x, int *y, int *dir, int alpha, int beta) {
    int self = (depth % 2 == 0);

#ifdef USE_HASH
    unsigned int hash = encode(board, self);
#endif

    int value = board_value(board);

#ifdef DEBUG_LEVEL
    if (depth <= DEBUG_LEVEL) {
        printf("start call depth %d, turn: %d value: %d\n", depth, self, value);
        print_board(board);
    }
#endif

    if (value != 0) {

#ifdef USE_HASH
        if (value == VALUE_WIN) {
            set_used(hash, HASH_WIN);
        } else if (value == VALUE_LOSE) {
            set_used(hash, HASH_LOSE);
        }
#endif

        return value;
    }

#ifdef USE_HASH
    value = is_used(hash);
    if (value == HASH_WIN) {
        return VALUE_WIN;
    } else if (value == HASH_LOSE) {
        return VALUE_LOSE;
    } else if (value == HASH_VISITING) {
        return 0;
    }
#endif

    if (depth >= SEARCH_LEVEL) {
        return 0;
    }

#ifdef USE_HASH
    set_used(hash, HASH_VISITING);
#endif

    char board_next[5][5];
    int best_value = self ? MIN : MAX;
    int nx = -1, ny = -1, nd = -1;
    int temp_1, temp_2;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((self && board[i][j] == SELF) || (!self && board[i][j] == OPPONENT)) {
                for (int k = 0; k < 8; ++k) {
                    if (!go_direction(board, board_next, i, j, dx[k], dy[k], &temp_1, &temp_2)) {
                        continue;
                    }
                    int temp = run(board_next, depth + 1, &nx, &ny, &nd, alpha, beta);
                    value = self ? temp - depth : temp + depth;
                    // value = run(board_next, depth + 1, &nx, &ny, &nd, alpha, beta);

#ifdef DEBUG_LEVEL
                    if (depth < DEBUG_LEVEL) {
                        printf("returned from depth: %d, backed value: %d best value: %d nx: %d ny: %d nd: %d\n", depth + 1, value, best_value, nx, ny, nd);
                    }
#endif

                    if ((self && value > best_value) || (!self && value < best_value)) {

#ifdef DEBUG_LEVEL
                        if (depth < DEBUG_LEVEL) {
                            printf("update best value to: %d\n", value);
                        }
#endif

                        best_value = value;
                        if (self)
                            alpha = max(alpha, best_value);
                        if (!self)
                            beta = min(beta, best_value);
                        if (beta <= alpha)
                            break;
                        *x = i;
                        *y = j;
                        *dir = k;
                    }
                }
            }
        }
    }

#ifdef DEBUG_LEVEL
    if (depth < DEBUG_LEVEL) {
        printf("returning depth: %d best value: %d nx: %d ny: %d nd: %d\n", depth, best_value, *x, *y, *dir);
    }
#endif

#ifdef USE_HASH
    if (best_value == VALUE_WIN) {
        set_used(hash, HASH_WIN);
    } else if (best_value == VALUE_LOSE) {
        set_used(hash, HASH_LOSE);
    } else {
        set_used(hash, HASH_UNSEEN);
    }
#endif

    return best_value;
}