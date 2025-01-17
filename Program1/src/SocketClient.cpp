#include "SocketClient.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

SocketClient::SocketClient(const std::string& host, int port)
    : serverHost(host), serverPort(port), serverSocket(-1) {}

bool SocketClient::connectToServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Ошибка: не удалось создать сокет.\n";
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverHost.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Ошибка: неверный адрес сервера.\n";
        return false;
    }

    if (connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Ошибка: не удалось подключиться к серверу.\n";
        return false;
    }

    std::cout << "Подключение к серверу установлено.\n";
    return true;
}

void SocketClient::sendData(const std::map<char, int>& data) {
    if (serverSocket < 0) {
        std::cerr << "Ошибка: сокет не открыт.\n";
        return;
    }

    std::string serializedData;
    for (const auto& [ch, count] : data) {
        serializedData += ch;
        serializedData += std::to_string(count);
    }

    ssize_t bytesSent = send(socketFd, serializedData.c_str(), serializedData.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Ошибка отправки данных: " << strerror(errno) << "\n";
        std::cerr << "Закрытие клиента...\n";
        close(socketFd);
        socketFd = -1;
    }
}
