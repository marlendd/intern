#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <map>

class ThreadManager {
public:
    void run();

private:
    void handleInput();
    void processData(SocketClient& client);

    std::map<char, int> buffer;
    std::mutex bufferMutex;
    std::condition_variable bufferCondition;
    bool hasData = false;
};

#endif // THREADMANAGER_H
