#ifndef SERVER_H
#define SERVER_H

#define PORT 8080
#define BUFFER_SIZE 2048

void start_server();
void handle_client(int client_socket);

#endif