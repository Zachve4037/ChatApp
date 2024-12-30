#include "chat_utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int client_sockets[MAX_CLIENTS];

void process_message(const char *message) {
    printf("Spracovavanie spravy: %s\n", message);
}

void broadcast_message(const char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client_sockets[i] != 0 && client_sockets[i] != sender_socket) {
            write(client_sockets[i], message, strlen(message));
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}