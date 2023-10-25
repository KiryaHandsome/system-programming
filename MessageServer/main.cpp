#include "main.h"

#pragma comment(lib, "ws2_32.lib")


int main()
{
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0) {
		std::cout << "Startup failed with code " << result << '\n';
		return 1;
	}

	setHints();
	result = getaddrinfo(NULL, "7777", &hints, &serverInfo);
	if (result != 0) {
		std::stringstream ss;
		ss << "getaddrinfo error. Code : " << result << '\n';
		clear(ss.str());
		return false;
	}

	listenSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		clear("Connection ListenSocket failed.\n", serverInfo);
		return false;
	}

	result = bind(listenSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);
	if (result == SOCKET_ERROR) {
		clear("binding socket failed.\n", serverInfo, &listenSocket);
		return false;
	}

	result = listen(listenSocket, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		clear("listen failed.\n", serverInfo, &listenSocket);
		return false;
	}

	std::cout << "Server starts work.\n";
	
	SOCKET socket;
	while (true) {
		socket = accept(listenSocket, nullptr, nullptr);
		if (socket != INVALID_SOCKET) {
			connectionsInfo[socket] = "";
			std::cout << "Client #" << socket << " connected.\n";
			std::thread read_thread(&receiveMessageFromClient, socket);
			read_thread.detach();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	for (auto& pair : connectionsInfo) {
		closesocket(pair.first);
	}
	WSACleanup();
}

void setHints()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void clear(const std::string& message, addrinfo* info, SOCKET* socket)
{
	std::cout << message;
	if (info) {
		freeaddrinfo(info);
	}
	if (socket) {
		closesocket(*socket);
	}
}

void receiveMessageFromClient(SOCKET client)
{
	char receivebuffer[256];
	ZeroMemory(receivebuffer, 256);
	while (true) {
		ZeroMemory(receivebuffer, 256);
		if (recv(client, receivebuffer, 256, 0) > 0) {
			if (connectionsInfo[client] == "") {
				connectionsInfo[client] = receivebuffer;
				std::cout << "User " << connectionsInfo[client] << " authorized\n";
			}
			else {
				std::stringstream ss;
				ss << connectionsInfo[client] << ':' << receivebuffer << '\n';
				std::cout << ss.str();
				sendMessageToClients(ss.str().c_str(), client);
			}
		}
		else {
			std::cout << "Connection closed or error occured when receiving from " << connectionsInfo[client] << "\n"; 
			return;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void sendMessageToClients(const char* message, SOCKET from)
{
	for (auto& pair : connectionsInfo) {
		if (pair.first != from) {
			send(pair.first, message, strlen(message), 0);
		}
	}
}
