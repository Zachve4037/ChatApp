// server.c
#include "ipc_utils.h"
#include "chat_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

int server_socket;
char client_names[MAX_CLIENTS][100];

void handle_signal(int signal) {
    printf("Terminating server...\n");
    close_socket(server_socket);
    exit(0);
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];
    ssize_t bytes_read;
    int client_id = client_socket;

    bytes_read = read(client_socket, client_names[client_id], sizeof(client_names[client_id]) - 1);
    if (bytes_read > 0) {
        client_names[client_id][bytes_read] = '\0';
        printf("Client %d connected with name: %s\n", client_id, client_names[client_id]);
    }

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        char message_with_id[1100];
        snprintf(message_with_id, sizeof(message_with_id), "%s: %s", client_names[client_id], buffer);
        process_message(message_with_id);
        broadcast_message(message_with_id, client_socket);
    }

    printf("Client %s has logged out.\n", client_names[client_id]);
    close_socket(client_socket);
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client_sockets[i] == client_socket) {
            client_sockets[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    return NULL;
}

int main() {
    signal(SIGINT, handle_signal);

    server_socket = create_server_socket();
    printf("Server started...\n");

    while (1) {
        int client_socket = accept_client(server_socket);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_sockets[i] == 0) {
                client_sockets[i] = client_socket;
                pthread_t tid;
                pthread_create(&tid, NULL, handle_client, &client_socket);
                pthread_detach(tid);
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    close_socket(server_socket);
    return 0;
}