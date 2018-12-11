// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include "pch.h"
#pragma comment(lib,"ws2_32.lib")

#include<WS2tcpip.h>
#include <iostream>
#include "server.h"

#define BUFFER_SIZE = 4096
using namespace std;



int main()
{

	string ip = "127.0.0.1";
	const int  port = 54000;
	server _server(ip,port);
	
	///_server.connaction();
	


	return 0;
}


void server::connaction() {
	

	//wait for connaction 
	int clientSize = sizeof(client);
	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];  //client's remote name 
	char service[NI_MAXHOST];// service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0) {

		cout << host << "connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port " << ntohs(client.sin_port) << endl;

	}
	//close listening socket
	closesocket(listening);

	// while loop:accept and echo message bake to client
	char buf[4096];

	while (true) {
		ZeroMemory(buf, 4096);

		//wait for client and send data 

		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR) {
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}
		if (bytesReceived == 0) {
			cout << "client disconnected" << endl;
			break;
		}
		//Echo message back to client
		send(clientSocket, buf, bytesReceived + 1, 0);


	}
	//close the socket
	closesocket(clientSocket);
	//cleanup winsock
	WSACleanup();


}

void server::createSocket() {

	 listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket! Quitting";
	}
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.s_addr = INADDR_ANY;

	bind(listening,(sockaddr*)&hint, sizeof(hint));

	//tell winsock the socket is for listening 
	listen(listening,SOMAXCONN);

}

void server::initializeWinsock() {

	ver = MAKEWORD(2,2);
	int wsOK = WSAStartup(ver,&wsaData);
	if (wsOK != 0) {
		std::cerr << "can't Initialize winsock! Quitting " << std::endl;
		return;
	}

}




server::server(const std::string &ip,const int &port) :ip(ip),port(port) {
	buffer = new char[3];
	initializeWinsock();
	createSocket();
	connaction();

}

server::~server() {

}