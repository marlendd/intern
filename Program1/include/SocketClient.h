#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <string>
#include <map>

class SocketClient {
public:
    SocketClient(const std::string& host, int port);
    ~SocketClient();
    bool connectToServer();
    void sendData(const std::map<char, int>& data);

private:
    std::string serverHost;
    int serverPort;
    int clientSocket;
};

#endif // SOCKETCLIENT_H
