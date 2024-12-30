#ifndef CHAT_UTILS_H
#define CHAT_UTILS_H

#include <pthread.h>

#define MAX_CLIENTS 100

extern pthread_mutex_t clients_mutex;
extern int client_sockets[];

void process_message(const char *message);
void broadcast_message(const char *message, int sender_socket);

#endif // CHAT_UTILS_H