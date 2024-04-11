#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdbool.h>

void drawBoard(char board[]);
int checkValidity(char board[], int position);
void putMark(int position, char mark, char board[]);
char checkWinner(char board[]);
bool checkDraw(char board[]);
int getInput();
#endif // TICTACTOE_H
