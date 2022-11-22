#ifndef HASH_H
#define HASH_H
extern char SELF;
extern char OPPONENT;
unsigned int encode(char board[][5], int self);
unsigned char used[1 << 29];
void reset_used();
void set_bit(unsigned int hash, int value);
void set_used(unsigned int hash, int value);
int is_used(unsigned int hash);
#endif