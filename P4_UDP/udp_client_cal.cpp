// udp_trig_client.cpp
#include <iostream>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 9095
#define BUF 1024

int main() {
    WSADATA wsa;
    SOCKET s;
    sockaddr_in serv{};
    int slen, n;
    char buf[BUF];
    char angle_str[50];

    WSAStartup(MAKEWORD(2,2), &wsa);

    // UDP socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");   // server IP (localhost)

    slen = sizeof(serv);

    // Get angle from user
    cout << "Enter angle in degrees: ";
    cin >> angle_str;

    // Send angle to server
    sendto(s, angle_str, (int)strlen(angle_str) + 1, 0,
           (sockaddr*)&serv, slen);

    // Receive result from server
    n = recvfrom(s, buf, BUF - 1, 0, (sockaddr*)&serv, &slen);
    buf[n] = '\0';

    cout << "From server: " << buf << "\n";

    closesocket(s);
    WSACleanup();
    return 0;
}
