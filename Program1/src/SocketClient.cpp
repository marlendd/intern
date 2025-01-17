#include "SocketClient.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

SocketClient::SocketClient(const std::string& host, int port)
    : serverHost(host), serverPort(port), clientSocket(-1) {}

SocketClient::~SocketClient() {
    if (clientSocket != -1) {
        close(clientSocket); // закрытие сокета при завершении работы
    }
}

bool SocketClient::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); // создаём сокет
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverHost.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    std::cout << "Connected to server.\n";
    return true;
}

void SocketClient::sendData(const std::map<char, int>& data) {
    if (clientSocket == -1) {
        std::cerr << "Socket is not connected.\n";
        return;
    }

    std::string serializedData;
    for (const auto& [key, value] : data) {
        serializedData += key;
        serializedData += std::to_string(value);
    }

    ssize_t bytesSent = send(clientSocket, serializedData.c_str(), serializedData.size(), 0);
    if (bytesSent < 0) {
        std::cerr << "Failed to send data.\n";
    } else {
        std::cout << "Data sent successfully.\n";
    }
}
