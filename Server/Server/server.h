#pragma once
#include "params.h"
#include "multiConnection.h"

class server {

	WSADATA wsaData;
	WORD ver;
	SOCKET listening;
	SOCKET clientSocket;
	sockaddr_in hint;
	sockaddr_in client;
	char * buffer=nullptr;
	multiConnection* clients = nullptr;
	static server * _server;
	static bool init;
	
	server();
	
public:
	

	~server();
    void initializeWinsock();
    void createListeningSocket();
	void connaction();
	void shutdownServer();
	static const server& instanceServer();

};


