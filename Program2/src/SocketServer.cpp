#include "SocketServer.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

SocketServer::SocketServer(int port) : serverPort(port) {}

void SocketServer::run() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket.\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket.\n";
        return;
    }

    listen(serverSocket, 5);
    std::cout << "Server is running on port " << serverPort << "...\n";

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept connection.\n";
            continue;
        }

        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);

        std::map<char, int> charCount;
        std::string data(buffer);
        for (size_t i = 0; i < data.size(); i += 2) {
            charCount[data[i]] = data[i + 1] - '0';
        }

        std::vector<std::pair<char, int>> sortedData(charCount.begin(), charCount.end());
        std::sort(sortedData.begin(), sortedData.end(), [](auto& a, auto& b) {
            return a.second < b.second;
        });

        for (const auto& [key, value] : sortedData) {
            std::cout << key << ": " << value << "\n";
        }
        close(clientSocket);
    }
}
