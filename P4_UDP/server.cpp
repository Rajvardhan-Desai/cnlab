#include<iostream>
#include<cstring>
#include<winsock2.h>
#include<fstream>
#pragma comment(lib,"ws2_32.lib")

#define PORT 9099
#define BUF 1024

using namespace std;

int main(){


	WSADATA wsa;
	SOCKET s, ns;
	sockaddr_in serv{},cli{};
	char buf[BUF],fname[250];

	WSAStartup(MAKEWORD(2,2),&wsa);

	s = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(PORT);
	
	
	bind(s,(sockaddr*)&serv,sizeof(serv));
	listen(s,5);

	cout << "Server Waiting..." << endl;

	int len = sizeof(cli);
	
	ns = accept(s, (sockaddr*)&cli,&len);

	int n = recv(ns,fname,sizeof(fname),0);

	
	
	fname[n] = '\0';
	
	ifstream fin(fname, ios::binary);

	if(!fin){
		cout << "file not found";
		closesocket(ns);
		closesocket(s);
		WSACleanup();
		return 0;
	}

	while((n = (int)fin.read(buf,BUF).gcount()) > 0){
		send(ns,buf,n, 0);
	}

	
	fin.close();

	// cout << "From Client : " << buf << endl;
	// strcpy(buf, "hello from server");
	// send(ns,buf,strlen(buf),0);

	closesocket(ns);

	closesocket(s);

	WSACleanup();

	return 0;

}