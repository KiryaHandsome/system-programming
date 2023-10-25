#pragma once

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <sstream>
#include <list>
#include <map>


WSAData data;

addrinfo hints;
addrinfo* serverInfo = nullptr;
SOCKET listenSocket;
bool itWorks = true;
std::map<SOCKET, std::string> connectionsInfo;


void setHints();

void clear(const std::string& message, addrinfo* info = nullptr, SOCKET* socket = nullptr);

void receiveMessageFromClient(SOCKET client);

void sendMessageToClients(const char* buffer, SOCKET from);