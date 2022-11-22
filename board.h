#ifndef BOARD_H
#define BOARD_H
extern char SELF;
extern char OPPONENT;
void print_board(char board[][5]);
int in_bound(int x, int y);
int board_value(char board[][5]);
int go_direction(char board[][5], char board_next[][5], int x, int y, int dx, int dy);
int go_opponent(char board[][5], char *cmd);
#endif