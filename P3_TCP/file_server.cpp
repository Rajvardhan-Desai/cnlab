// server.cpp  (send requested file)
#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define PORT 9090
#define BUF 1024

int main() {
    WSADATA wsa;
    SOCKET ls, cs;
    sockaddr_in serv{}, cli{};
    int clen, n;
    char buf[BUF], fname[260];

    WSAStartup(MAKEWORD(2,2), &wsa);

    ls = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(ls, (sockaddr*)&serv, sizeof(serv));
    listen(ls, 5);

    cout << "Server listening...\n";
    clen = sizeof(cli);
    cs = accept(ls, (sockaddr*)&cli, &clen);

    // receive filename
    n = recv(cs, fname, sizeof(fname), 0);
    fname[n] = '\0';
    cout << "Client requested: " << fname << "\n";

    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "File not found\n";
        closesocket(cs);
        closesocket(ls);
        WSACleanup();
        return 0;
    }

    // send file data
    while (!fin.eof()) {
        fin.read(buf, BUF);
        n = (int)fin.gcount();
        if (n > 0) send(cs, buf, n, 0);
    }

    fin.close();
    closesocket(cs);
    closesocket(ls);
    WSACleanup();
    return 0;
}
