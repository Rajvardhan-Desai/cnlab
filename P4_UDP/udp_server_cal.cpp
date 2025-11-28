// udp_trig_server.cpp
#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <cmath>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 9095
#define BUF 1024
#define PI 3.14159265

int main() {
    WSADATA wsa;
    SOCKET s;
    sockaddr_in serv{}, cli{};
    int clen, n;
    char buf[BUF];

    WSAStartup(MAKEWORD(2,2), &wsa);

    // UDP socket
    s = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    // Bind
    bind(s, (sockaddr*)&serv, sizeof(serv));

    cout << "UDP Trig Server waiting on port " << PORT << "...\n";

    clen = sizeof(cli);

    // Receive angle in degrees from client
    n = recvfrom(s, buf, BUF - 1, 0, (sockaddr*)&cli, &clen);
    buf[n] = '\0';

    cout << "Received angle (degrees): " << buf << "\n";

    double angle_deg = atof(buf);
    double angle_rad = angle_deg * PI / 180.0;

    double s_val = sin(angle_rad);
    double c_val = cos(angle_rad);
    double t_val = tan(angle_rad);

    // Prepare result string
    char result[BUF];
    sprintf(result, "sin(%.2f)=%.4f, cos(%.2f)=%.4f, tan(%.2f)=%.4f",
            angle_deg, s_val, angle_deg, c_val, angle_deg, t_val);

    // Send result back to client
    sendto(s, result, (int)strlen(result) + 1, 0, (sockaddr*)&cli, clen);

    closesocket(s);
    WSACleanup();
    return 0;
}
