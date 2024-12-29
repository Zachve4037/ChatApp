cmake_minimum_required(VERSION 3.30)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled client.c
        ipc_utils.c
        ipc_utils.h
        chat_utils.c
        chat_utils.h)
