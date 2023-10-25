#pragma once


#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <sstream>


WSAData data;

addrinfo hints;
addrinfo* serverInfo = nullptr;

SOCKET connectSocket;

std::thread receive_thread;

void clear(const std::string& message, addrinfo* info = nullptr, SOCKET* socket = nullptr);