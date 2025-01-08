// client.c
#include "ipc_utils.h"
#include "chat_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *receive_messages(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
    }

    return NULL;
}

int main() {
    int client_socket = connect_to_server(SOCKET_PATH);
    printf("Connected to server...\n");

    char name[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    write(client_socket, name, strlen(name));

    pthread_t tid;
    pthread_create(&tid, NULL, receive_messages, &client_socket);
    pthread_detach(tid);

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strncmp(buffer, "exit", 4) == 0) {
            snprintf(buffer, sizeof(buffer), "%s has disconnected.", name);
            write(client_socket, buffer, strlen(buffer));
            break;
        }
        write(client_socket, buffer, strlen(buffer));
    }

    close_socket(client_socket);
    return 0;
}