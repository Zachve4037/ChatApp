#include "ipc_utils.h"
#include "chat_utils.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_server_socket() {
    int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    return server_socket;
}

int accept_client(int server_socket) {
    return accept(server_socket, NULL, NULL);
}

int connect_to_server(const char *socket_path) {
    int client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    return client_socket;
}

void close_socket(int socket) {
    close(socket);
}