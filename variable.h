#ifndef VARIABLES_H
#define VARIABLES_H

// Setting macros.
#define SEARCH_LEVEL 7
#define USE_HASH 1
// #define DEBUG_LEVEL 1

// Internal macros.
#define EMPTY ' '

#define HASH_UNSEEN 0
#define HASH_WIN 1
#define HASH_LOSE 2
#define HASH_VISITING 3
#define HASH_MASK 3

#define VALUE_WIN 100
#define VALUE_LOSE -999
#define MAX 1001
#define MIN -1001

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#endif