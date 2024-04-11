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
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connection
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size)) == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    // Game variables
    char board[9] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };
    // char boardCopy[9];
    char serverMark = 'O', clientMark = 'X';
    bool turn = true; // true for server's turn, false for client's
    
    int count = 0;
    // Game loop
    while (1) {
        int position;

        // Server's turn
 
        printf("Turn for server.\n");
        drawBoard(board); // Call the drawBoard function

        // Get valid position from server (implementation not shown)
        do {
            // printf("Enter your position (1-9): ");
            position = getInput();
            // scanf("%d", &position);
        } while (!checkValidity(board, position));

        // Update board
        putMark(position, serverMark, board);

        // Check for winner or draw (implementation not shown)
        if (checkWinner(board) == serverMark) {
            printf("Server wins!\n");
            send(client_socket, board, sizeof(board), 0);
            break;
        }
        if (checkDraw(board)) {
          printf("Draw\n");
          send(client_socket, board, sizeof(board), 0);
          break;
        }
        
        printf("Waiting for the client response.\n");

        // Send updated board and turn
        if (send(client_socket, board, sizeof(board), 0) < 0) {
          perror("Sending board error from server.\n");
          exit(EXIT_FAILURE);
        }
        // send(client_socket, &turn, sizeof(turn), 0);

        memset(board, 0, sizeof(board));
        if (recv(client_socket, board, sizeof(board), 0) <= 0) {
            perror("Receive failed\n");
            break;
        }
        // Handle client wins
        if (checkWinner(board) == clientMark) {
            drawBoard(board);
            printf("Client wins! You lose!\n");
            break;
        } 
    }
    printf("Game Over!\n");

    // Close sockets
    close(server_socket);
    close(client_socket);

    return 0;
}
