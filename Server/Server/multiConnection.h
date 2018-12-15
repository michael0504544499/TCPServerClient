#pragma once

#include "params.h"



class client;

	class multiConnection {


		std::unordered_map<SOCKET*, client*>* clientSockets;


	public:
		multiConnection();
		~multiConnection();
		void insertClientSocket(SOCKET clientSocket, client* newClient);
		void deleteClientSocet(SOCKET clientSocket);
		const std::unordered_map<SOCKET*, client*>& getClientSockets();
		void con(SOCKET clientSocket);

	};




