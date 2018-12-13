// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include "pch.h"
#include "params.h"






using namespace std;


bool server::init = true;
server* server::_server = nullptr;


int main()
{

	server::instanceServer();


	return 0;
}


void server::connaction() {
	
	while (true) {

		//wait for connaction 
		int clientSize = sizeof(client);
		clientSocket = accept(listening, (sockaddr*)&client, &clientSize);


		this->clients->insertClientSocket(clientSocket, client);

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

		clients->con(clientSocket);


		
		shutdownServer();
	}
	
}



void server::shutdownServer() {
	
	//close the socket
	closesocket(clientSocket);
	//cleanup winsock
	WSACleanup();
	delete server::_server;
}




void server::createListeningSocket() {

	 listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket! Quitting";
	}
	
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	inet_pton(AF_INET,IP_ADDRESS.c_str(), &(hint.sin_addr.s_addr));
	
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



server::server(){
	server::init = false;
	buffer = new char[BUFFER_SIZE];
	this->clients = new multiConnection();
	initializeWinsock();
	createListeningSocket();
	connaction();

}



server::~server() {
	cout << "desturactor called"<<endl;
	delete server::buffer;
	delete server::_server;
	delete this->clients;
}



const server& server::instanceServer() {
	
	if (server::init) {
		server::_server = new server();
		server::init = false;
		return *server::_server;
	}
	return *server::_server;

}





