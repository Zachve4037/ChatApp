cmake_minimum_required(VERSION 3.25.1)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(server server.c
        ipc_utils.c
        chat_utils.c
)

add_executable(client client.c
        ipc_utils.c
        chat_utils.c
)