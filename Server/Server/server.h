#pragma once
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<WS2tcpip.h>



#define BUFFER_SIZE = 4096

class server {

	WSADATA wsaData;
	WORD ver;
	SOCKET listening;
	SOCKET clientSocket;
	sockaddr_in hint;
	sockaddr_in client;
	char * buffer=nullptr;
	int port;
	std::string ip;

public:
	server(const std::string &ip, const int  &port);

	~server();
    void initializeWinsock();
    void createSocket();
	void connaction();

};


