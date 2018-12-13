#pragma once
#include "pch.h"
#include "params.h"




void multiConnection::con(SOCKET clientSocket) {

	char  buffer[BUFFER_SIZE];

	while (true) {
		ZeroMemory(buffer, BUFFER_SIZE);

		//wait for client and send data 

		int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Error in recv(). Quitting" << std::endl;
			break;
		}
		if (bytesReceived == 0) {
			std::cout << "client disconnected" << std::endl;
			break;
		}

		//Echo message back to client
		send(clientSocket, buffer, bytesReceived + 1, 0);


	}


}




multiConnection::multiConnection()
{
	multiConnection::clientSockets=new std::unordered_map<SOCKET*, sockaddr_in*>();
	
}

multiConnection::~multiConnection()
{
	delete clientSockets;
}

void multiConnection::insertClientSocket(SOCKET clientSocket, sockaddr_in clientSockAddr)
{

	if (this->clientSockets->count(&clientSocket) >= 0) {
		this->clientSockets->insert({ &clientSocket,&clientSockAddr });
	}

}

void multiConnection::deleteClientSocet(SOCKET clientSocket, sockaddr_in clientSockAddr)
{
	if (this->clientSockets->count(&clientSocket) > 0) {
		this->clientSockets->erase(&clientSocket);
	}
}

const std::unordered_map<SOCKET*, sockaddr_in*>& multiConnection::getClientSockets()
{
	return *clientSockets;
}


