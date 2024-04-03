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
//    int client_socket;
//    struct sockaddr_in server_addr;
//    char buffer[BUFFER_SIZE];
//
//    // Create socket
//    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//    {
//        perror("Socket creation failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Initialize server address
//    memset(&server_addr, 0, sizeof(server_addr));
//    server_addr.sin_family = AF_INET;
//    // We need to replace IP address with actual server IP address
//    server_addr.sin_addr.s_addr = inet_addr("192.168.1.71");
//    server_addr.sin_port = htons(PORT);
//
//    // Connect to server
//    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
//    {
//        perror("Connection failed");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Connected to server\n");
//
//    // Send and receive messages
//    while (1)
//    {
//        printf("Client: ");
//        fgets(buffer, BUFFER_SIZE, stdin);
//        if (send(client_socket, buffer, strlen(buffer), 0) == -1)
//        {
//            perror("Send failed");
//            exit(EXIT_FAILURE);
//        }
//
//        memset(buffer, 0, BUFFER_SIZE);
//        if (recv(client_socket, buffer, BUFFER_SIZE, 0) == -1)
//        {
//            perror("Receive failed");
//            exit(EXIT_FAILURE);
//        }
//
//        printf("Server: %s", buffer);
//    }
//
//    // Close socket
//    close(client_socket);
//
//    return 0;
//}