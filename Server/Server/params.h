#pragma once
#include "pch.h"
#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include <iostream>
#include <unordered_map>
#include "server.h"
#include "client.h"


const int BUFFER_SIZE = 4096;
const int PORT = 54000;
const std::string IP_ADDRESS = "127.0.0.1";
