#pragma once
#include "pch.h"
#include "params.h"


class client {


SOCKET clientSocket;
sockaddr_in socketAddr;
char * buffer = nullptr;

public:
	client();
	~client();
	const SOCKET& getClientSocket()const;
	const sockaddr_in& getSocketAddr()const;
	void setClientSocket(SOCKET clientSocket);
	void setSocketAddr(sockaddr_in socketaddr);





};
