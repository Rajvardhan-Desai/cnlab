// win_cpp_hello_client.cpp
#include <iostream>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define PORT 8000  

int main() {
    WSADATA wsa;
    SOCKET s;
    sockaddr_in serv{};
    char buf[100];
    int n;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "WSAStartup failed\n";
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Socket creation failed\n";
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(s, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR) {
        cout << "Connect failed\n";
        closesocket(s);
        WSACleanup();
        return 1;
    }

    strcpy(buf, "Hello from Client");
    send(s, buf, (int)strlen(buf), 0); // no need for +1

    n = recv(s, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        cout << "From server: " << buf << "\n";
    }

    closesocket(s);
    WSACleanup();
    return 0;
}
