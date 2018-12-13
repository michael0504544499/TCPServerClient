#pragma once
#include "params.h"




	class multiConnection {




		std::unordered_map<SOCKET*, sockaddr_in*>* clientSockets;



	public:
		multiConnection();
		~multiConnection();
		void insertClientSocket(SOCKET clientSocket, sockaddr_in clientSockAddr);
		void deleteClientSocet(SOCKET clientSocket, sockaddr_in clientSockAddr);
		const std::unordered_map<SOCKET*, sockaddr_in*>& getClientSockets();
		void con(SOCKET clientSocket);

	};




