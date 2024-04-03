//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
//
//#define PORT 8000
//#define BUFFER_SIZE 1024
//
//int main() {
//    int server_socket, client_socket;
//    struct sockaddr_in server_addr, client_addr;
//    socklen_t addr_size = sizeof(struct sockaddr_in);
//    char buffer[BUFFER_SIZE];
//
//    // Create socket
//    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        perror("Socket creation failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Initialize server address
//    memset(&server_addr, 0, sizeof(server_addr));
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    server_addr.sin_port = htons(PORT);
//
//    // Bind the socket
//    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
//        perror("Bind failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Listen for incoming connections
//    if (listen(server_socket, 5) == -1) {
//        perror("Listen failed");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Server listening on port %d\n", PORT);
//
//    // Accept incoming connection
//    if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_size)) == -1) {
//        perror("Accept failed");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Client connected\n");
//
//    // Receive and send messages
//    while (1) {
//        memset(buffer, 0, BUFFER_SIZE);
//        if (recv(client_socket, buffer, BUFFER_SIZE, 0) == -1) {
//            perror("Receive failed");
//            exit(EXIT_FAILURE);
//        }
//
//        printf("Client: %s", buffer);
//
//        printf("Server: ");
//        fgets(buffer, BUFFER_SIZE, stdin);
//        if (send(client_socket, buffer, strlen(buffer), 0) == -1) {
//            perror("Send failed");
//            exit(EXIT_FAILURE);
//        }
//    }
//
//
//
//    close(server_socket);
//    close(client_socket);
//
//    return 0;
//}