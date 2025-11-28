// client.cpp  (request and receive file)
#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define PORT 9090
#define BUF 1024

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in serv{};
    char buf[BUF];
    int n;
    string filename = "abc.txt";

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");   // localhost

    connect(sock, (sockaddr*)&serv, sizeof(serv));

    // send filename (with '\0' so server knows where it ends)
    send(sock, filename.c_str(), (int)filename.length() + 1, 0);

    // receive file and save
    ofstream fout("received_" + filename, ios::binary);
    while ((n = recv(sock, buf, BUF, 0)) > 0) {
        fout.write(buf, n);
    }

    cout << "File saved as received_" << filename << "\n";

    fout.close();
    closesocket(sock);
    WSACleanup();
    return 0;
}
