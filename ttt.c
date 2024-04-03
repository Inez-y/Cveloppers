#include <stdio.h>
#include <stdbool.h>
#define MAX_NAME_LENGTH 256

// Create board in global scope
char board[9] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
};

#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

void drawBoard() {
    printf("-------------\n");
    for (int n = 1; n <= 9; n++) {
        if (n % 3 == 1) {
            printf("|");
        }
        if (board[n - 1] == 'X') {
            printf(RED "%c" RESET " | ", board[n - 1]);
        } else if (board[n - 1] == 'O') {
            printf(BLUE "%c" RESET " | ", board[n - 1]);
        } else {
            printf(" %c |", board[n - 1]);
        }
        if (n % 3 == 0) {
            printf("\n-------------\n");
        }
    }
}

// Check if the position that a user entered is already occupied
bool checkValidity(int position) {
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

// Prompt users to enter number
int getInput() {
    int value;
    while (1) {
        printf("Please enter the number of the spot: \n");
        // If it's not a number (if the below scanf function fails), continue teo prompt user to
        // enter number
        if (scanf("%d", &value) != 1) {
            printf("You can only enter the number from 1 to 9.\n");
            while (getchar() != '\n');
            continue;
        }

        // If the entered number is not in the correct range, continue to prompt user
        if (value <= 0 || value >= 10) {
            printf("You can only enter the number from 1 to 9.\n");
            continue;
        }
            // If the entered number is in the correct range
        else {
            // But the number is already occupied, continue to prompt user
            if (!checkValidity(value)) {
                continue;
            }
            // And it's not occupied, return value
            return value;
        }

    }
}

// Set mark on the board
void putMark(int position, char mark) {
    board[position] = mark;
    drawBoard();
}

// Check winner
char checkWinner() {
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

// Run game
void run() {
    char serverMark = 'O';
    char clientMark = 'X';

    printf("Game Start!\n");
    printf("Mark for server is 'O'\n");
    printf("Mark for client is 'X'\n");

    drawBoard();

    // Game counter
    int c = 0;

    while (1) {
        // main condition
        // c % 2 == 0 means the turn of the server
        // c % 2 != 0 means the turn of the client
        if (c % 2 == 0) {
            printf("Turn for server.\n");
            printf("Your mark is 'O'\n");
        } else {
            printf("Turn for client.\n");
            printf("Your mark is 'X'\n");
        }

        int position = getInput() - 1;

        if (c % 2 == 0) {
            putMark(position, serverMark);
        } else {
            putMark(position, clientMark);
        }
        c++;

        char winner = checkWinner();
        if (winner == 'O' || winner == 'X') {
            if (winner == serverMark) {
                printf("Server Win!\n");
            } else if (winner == clientMark) {
                printf("Client Win!\n");
            }
            printf("Game End\n");
            break;
        } else {
            if (c == 9) {
                printf("Draw!\n");
                printf("Game End\n");
                break;
            } else {
                continue;
            }
        }
    }
}

int main() {
    run();
    return 0;
}
