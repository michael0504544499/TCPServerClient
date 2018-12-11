// Server.cpp 
#include "pch.h"

#pragma comment(lib,"ws2_32.lib")
#include<WS2tcpip.h>
#include<string>
#include <iostream>


using namespace std;

int main()
{
	string ipaddress = "127.0.0.1";
	int port = 54000;

	//initialize winsoc
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "Can't start winsock, Err #" << wsResult << endl;
		return 0;
	}



	//create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket,Err #" << WSAGetLastError() << endl;
		return 0;
	}


	//filll in hint structure 
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);


	//connect to server 
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}




	// do while loop to send and receive data
	char buf[4096];
	string userInput;

	do {
		//prompt the user for some text
		cout << "> ";
		getline(cin, userInput);
		if (userInput.size() > 0) {// make sure the user has typed in somthing

			//Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {


				//Wait for response
				ZeroMemory(buf, 4096);
				int byteReveived = recv(sock, buf, 4096, 0);
				if (byteReveived > 0) {
					//Echo response to console
					cout << "SERVER>" << string(buf, 0, byteReveived) << endl;
				}

			}
		}
	} while (userInput.size() > 0);

	//Gracefully close down everything 
	closesocket(sock);
	WSACleanup();

	return 0;
}

