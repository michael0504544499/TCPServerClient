#pragma once
#include "params.h"
#include "multiConnection.h"


class server {

	WSADATA wsaData;
	WORD ver;
	SOCKET listening;
	sockaddr_in hint;
	multiConnection* clients = nullptr;
	static server * _server;
	static bool init;
	
	server();
	
public:
	

	~server();
    void initializeWinsock();
    void createListeningSocket();
	void connaction();
	void shutdownServer(SOCKET clientSocket);
	static const server& instanceServer();

};


