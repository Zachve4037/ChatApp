#ifndef IPC_UTILS_H
#define IPC_UTILS_H

#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_CLIENTS 10

int create_server_socket();
int accept_client(int server_socket);
int connect_to_server(const char *path);
void close_socket(int socket_fd);

#endif //IPC_UTILS_H
