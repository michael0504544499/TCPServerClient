#pragma once
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<WS2tcpip.h>




class server {

	WSADATA wsaData;
	WORD ver;
	SOCKET listening;
	SOCKET clientSocket;
	sockaddr_in hint;
	sockaddr_in client;
	char * buffer=nullptr;
	static server * _server;
	static bool init;
	server();
	//const std::string &ip, const int  &port
public:
	

	~server();
    void initializeWinsock();
    void createSocket();
	void connaction();
	void shutdownServer();
	static const server& instanceServer();

};


