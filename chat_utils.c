#include "chat_utils.h"
#include <stdio.h>
#include <string.h>

void broadcast_message(const char *message, int exclude_socket) {
    // Odošle správu všetkým klientom okrem toho s exclude_socket.
}

void process_message(const char *message) {
    // Validácia a spracovanie správy.
    printf("Processed message: %s\n", message);
}