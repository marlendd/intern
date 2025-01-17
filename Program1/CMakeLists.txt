cmake_minimum_required(VERSION 3.10)
project(Program1)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Program1
    src/main.cpp
    src/ThreadManager.cpp
    src/Buffer.cpp
    src/SocketClient.cpp
)
target_link_libraries(Program1 pthread)
