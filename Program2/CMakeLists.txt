cmake_minimum_required(VERSION 3.10)
project(Program2)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Program2
    src/main.cpp
    src/SocketServer.cpp
)

