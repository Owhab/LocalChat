#include "ChatServer.hpp"
#include <iostream>

int main()
{
    ChatServer server(12345);
    server.start();
    return 0;
}