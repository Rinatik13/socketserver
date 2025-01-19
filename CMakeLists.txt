cmake_minimum_required(VERSION 3.29)
project(socketserver)

set(CMAKE_CXX_STANDARD 20)

add_executable(socketserver
        src/main.cpp
        src/client.cpp
        src/client.h
        src/emptys/message.cpp
        src/emptys/message.h)
