#ifndef IPC_UTILS_H
#define IPC_UTILS_H

#define SOCKET_PATH "/tmp/chat_socket"

int create_server_socket();
int accept_client(int server_socket);
int connect_to_server(const char *socket_path);
void close_socket(int socket);

#endif