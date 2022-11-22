#ifndef ALGO_H
#define ALGO_H
extern int dx[8];
extern int dy[8];
extern char SELF;
extern char OPPONENT;
int run(char board[][5], int depth, int *x, int *y, int *dir, int alpha, int beta);
#endif