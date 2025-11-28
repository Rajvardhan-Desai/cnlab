// udp_file_server.cpp
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 9099
#define BUF 1024

int main() {
    WSADATA wsa;
    SOCKET s;
    sockaddr_in serv{}, cli{};
    int clen, n;
    char buf[BUF], fname[260];

    // 1. Init Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // 2. Create UDP socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    // 3. Fill server address and bind
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(s, (sockaddr*)&serv, sizeof(serv));

    cout << "UDP file server waiting on port " << PORT << "...\n";

    // 4. Receive filename from client
    clen = sizeof(cli);
    n = recvfrom(s, fname, sizeof(fname) - 1, 0, (sockaddr*)&cli, &clen);
    fname[n] = '\0';
    cout << "Client requested file: " << fname << "\n";

    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "File not found\n";
        closesocket(s);
        WSACleanup();
        return 0;
    }

    // 5. Send file data in chunks
    while ((n = (int)fin.read(buf, BUF).gcount()) > 0) {
        sendto(s, buf, n, 0, (sockaddr*)&cli, clen);
    }

    // 6. Send EOF marker to indicate end of file
    strcpy(buf, "EOF");
    sendto(s, buf, 3, 0, (sockaddr*)&cli, clen);

    fin.close();
    closesocket(s);
    WSACleanup();
    return 0;
}
