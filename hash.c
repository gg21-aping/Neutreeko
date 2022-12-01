#include "hash.h"
#include "variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_HASH

unsigned char used[1 << 29];

unsigned int encode(char board[][5], int self) {
    int positions[6];
    int n = 0;
    unsigned int hash = self;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == SELF) {
                positions[n++] = i * 5 + j;
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == OPPONENT) {
                positions[n++] = i * 5 + j;
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        hash = (hash << 5) + positions[i];
    }
    return hash;
}

void reset_used() {
    for (unsigned int i = 0; i < (1 << 29); ++i) {
        used[i] = 0;
    }
}

void set_bit(unsigned int hash, int value) {
    if (value) {
        used[hash / 8] |= 1 << (hash % 8);
    } else {
        used[hash / 8] &= ~(1 << (hash % 8));
    }
}

// value is in [0, 1, 2, 3].
void set_used(unsigned int hash, int value) {
    int low_bit = hash <<= 1;
    int high_bit = low_bit + 1;
    set_bit(low_bit, value & 1);
    set_bit(high_bit, value >> 1);
}

int is_used(unsigned int hash) {
    hash <<= 1;
    return (used[hash / 8] & (HASH_MASK << hash % 8)) >> (hash % 8);
}
#endif