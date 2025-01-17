#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <string>

class SocketServer {
public:
    explicit SocketServer(int port);
    void run();

private:
    int serverPort;
};

#endif // SOCKETSERVER_H
