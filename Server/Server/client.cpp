#pragma once
#include "pch.h"
#include "client.h"



client::client()
{
	buffer = new char[BUFFER_SIZE];
}

client::~client()
{
	delete buffer;
}

const SOCKET & client::getClientSocket() const
{
	return this->clientSocket;
}

const sockaddr_in & client::getSocketAddr() const
{
	return this->socketAddr;
}

void client::setClientSocket(SOCKET clientSocket)
{
	this->clientSocket = clientSocket;
}

void client::setSocketAddr(sockaddr_in socketaddr)
{
	this->socketAddr = socketaddr;
}
