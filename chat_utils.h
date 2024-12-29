#ifndef CHAT_UTILS_H
#define CHAT_UTILS_H

void broadcast_message(const char *message, int exclude_socket);
void process_message(const char *message);

#endif // CHAT_UTILS_H