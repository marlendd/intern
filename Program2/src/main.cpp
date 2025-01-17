#include "SocketServer.h"

int main() {
    SocketServer server(5000);
    server.run();
    return 0;
}
