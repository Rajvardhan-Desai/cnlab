// udp_file_client.cpp
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
    sockaddr_in serv{};
    int slen, n;
    char buf[BUF];
    string filename = "abc.txt";   // file to request

    // 1. Init Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // 2. Create UDP socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    // 3. Fill server address
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");  // server IP

    slen = sizeof(serv);

    // 4. Send filename to server
    sendto(s, filename.c_str(), (int)filename.length() + 1, 0,
           (sockaddr*)&serv, slen);

    // 5. Open output file to save received data
    ofstream fout("udp_received_" + filename, ios::binary);

    // 6. Receive file data until we get "EOF"
    while (true) {
        n = recvfrom(s, buf, BUF, 0, (sockaddr*)&serv, &slen);
        if (n <= 0) break;

        // check EOF marker
        if (n == 3 && buf[0] == 'E' && buf[1] == 'O' && buf[2] == 'F') {
            break;
        }

        fout.write(buf, n);
    }

    cout << "File saved as received_" << filename << "\n";

    fout.close();
    closesocket(s);
    WSACleanup();
    return 0;
}
