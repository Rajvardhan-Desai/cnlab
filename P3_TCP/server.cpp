// win_cpp_hello_server.cpp
#include <iostream>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET s, ns;
    sockaddr_in serv{}, cli{};
    int len, n;
    char buf[100];

    WSAStartup(MAKEWORD(2,2), &wsa);   // init Winsock

    s = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(s, (sockaddr*)&serv, sizeof(serv));
    listen(s, 5);

    cout << "Server waiting...\n";
    len = sizeof(cli);
    ns = accept(s, (sockaddr*)&cli, &len);

    n = recv(ns, buf, sizeof(buf) - 1, 0);
    buf[n] = '\0';
    cout << "From client: " << buf << "\n";

    strcpy(buf, "Hello from Server");
    send(ns, buf, (int)strlen(buf) + 1, 0);

    closesocket(ns);
    closesocket(s);
    WSACleanup();
    return 0;
}
