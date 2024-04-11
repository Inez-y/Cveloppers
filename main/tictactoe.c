#include <stdio.h>
#include <stdbool.h>
#define MAX_NAME_LENGTH 256

// Draw board
void drawBoard(char board[]) {
    printf("-------------\n");
    for (int n = 1; n <= 9; n++) {
        if (n % 3 == 1) {
            printf("| %c |", board[n - 1]);
        }
        else if (n % 3 == 2) {
            printf(" %c |", board[n - 1]);
        }
        else if (n % 3 == 0) {
            printf(" %c |\n", board[n - 1]);
            printf("-------------\n");
        }

    }
}

int getInput() {
    int value;
    printf("Please enter the number of the spot.\n");
    while (1) {
        printf(">>> ");
        if (scanf("%d", &value) != 1) {
            printf("You can only enter the number from 1 to 9.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue;
        }
        if (value <= 0 || value >= 10) {
            printf("You can only enter the number from 1 to 9.\n");
            continue;
        } else {
            return value;
        }
    }
}


// Check if the position that a user entered is already occupied
bool checkValidity(char board[], int position) {
    // position - 1 because we are input of index + 1
    position = position - 1;

    // If board[position] is 'O' or 'X' which means it is already occupied returns false
    if (board[position] == 'O' || board[position] == 'X') {
        printf("That spot is already occupied.\n");
        printf("Please select another spot!\n");
        return false;
    }
    // else return true
    return true;
}


// Set mark on the board
void putMark(int position, char mark, char board[]) {
    position = position - 1;
    board[position] = mark;
    drawBoard(board);
}

// Check winner
char checkWinner(char board[]) {
    for (int i = 0; i < 7; i += 3) {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2])) {
            return board[i];
        }
    }
    for (int i = 0; i < 3; i++) {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6])) {
            return board[i];
        }
    }
    if ((board[0] == board[4]) && (board[4] == board[8])) {
        return board[0];
    }
    if ((board[2] == board[4]) && (board[4] == board[6])) {
        return board[2];
    }
    return 0;
}

bool checkDraw(char board[]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 'X' || board[i] == 'O') {
            count++;
        }
    }
    return count == 9;
}
