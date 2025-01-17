#include "ThreadManager.h"
#include "SocketClient.h"
#include <iostream>
#include <cctype>
#include <map>
#include <algorithm> // Для std::all_of

void ThreadManager::run() {
    // Создание клиентского сокета
    SocketClient client("127.0.0.1", 5000);
    client.connectToServer();

    // Запуск потоков
    std::thread inputThread(&ThreadManager::handleInput, this);
    std::thread processingThread([this, &client]() { this->processData(client); });

    // Ожидание завершения потоков
    inputThread.join();
    processingThread.join();
}

void ThreadManager::handleInput() {
    while (true) {
        std::string input;
        std::cout << "Введите строку (только буквы, максимум 64 символа): ";
        std::getline(std::cin, input);

        // Проверка длины строки
        if (input.size() > 64) {
            std::cout << "Ошибка: строка превышает 64 символа.\n";
            continue;
        }

        // Проверка на буквы
        if (!std::all_of(input.begin(), input.end(), ::isalpha)) {
            std::cout << "Ошибка: строка должна содержать только буквы.\n";
            continue;
        }

        // Подсчёт символов
        std::map<char, int> charCount;
        for (char ch : input) {
            charCount[ch]++;
        }

        // Запись в буфер
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            buffer = charCount;
            hasData = true;
        }
        bufferCondition.notify_one();
    }
}

void ThreadManager::processData(SocketClient& client) {
    while (true) {
        std::unique_lock<std::mutex> lock(bufferMutex);
        bufferCondition.wait(lock, [this]() { return hasData; });

        // Копирование данных из буфера
        auto data = buffer;
        buffer.clear();
        hasData = false;
        lock.unlock();

        // Вывод данных на экран
        std::cout << "Полученные данные:\n";
        for (const auto& [ch, count] : data) {
            std::cout << ch << ": " << count << "\n";
        }

        // Отправка данных на сервер
        client.sendData(data);
    }
}
