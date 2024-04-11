#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");
    fflush(stdout);

    // Game variables
    char board[9];
    char clientMark = 'X';
    char serverMark = 'O';
    // Game loop
    while (1) {
        int position;
        // memset(&turn, 0, sizeof(turn));
        printf("waiting for the server's input\n");
        memset(board, 0, sizeof(board));

        // Receive updated board from server
        if (recv(client_socket, board, sizeof(board), MSG_WAITALL) <= 0) {
            perror("Receive failed\n");
            break;
        }

        // Handle result
        if (checkWinner(board) == serverMark) {
            drawBoard(board);
            printf("Server wins! You lose!\n");
            break;
        } 
        if (checkDraw(board)) {
          printf("Draw\n");
          break;
        }

        // Client's turn
        printf("Turn for client.\n");
        drawBoard(board);

        // Get valid position from client (implementation not shown)
        do {
            // printf("Enter your position (1-9): ");
            // scanf("%d", &position);
            position = getInput();
        } while (!checkValidity(board, position));
        putMark(position, clientMark, board);

        // Check for winner or draw (implementation not shown)
        if (checkWinner(board) == clientMark) {
            printf("Client wins!\n");
            send(client_socket, board, sizeof(board), 0);
            break;
        }

        // Check for error when sending board to client
        if (send(client_socket, board, sizeof(board), 0) < 0) {
          perror("Sending board error from client.\n");
          exit(EXIT_FAILURE);
        }
        
 
    }
    printf("Game Over!\n");
     // Close socket
    close(client_socket);

    return 0;
}
