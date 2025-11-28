#include<iostream>
#include<cstring>
#include<fstream>
#include<winsock2.h>

#define PORT 9099
#define BUF 1024
using namespace std;

int main(){

	WSADATA wsa;
	SOCKET s;
	sockaddr_in serv{};
	char buf[BUF];
	int n = 0;

	string fname = "abc.txt";

	WSAStartup(MAKEWORD(2,2),&wsa);

	s = socket(AF_INET,SOCK_STREAM,0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(PORT);

	connect(s,(sockaddr*)&serv,sizeof(serv));

	send(s,fname.c_str(), (int)fname.length()+1,0);

	ofstream fout("recevied_" + fname, ios::binary);

	while((n = recv(s,buf,BUF,0))>0){
		fout.write(buf,n);
	}
	
	cout << "File saved as recevied_" << fname << "\n";

	fout.close();
	closesocket(s);
	WSACleanup();
	return 0;
	

}