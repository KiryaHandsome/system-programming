#include "main.h"

#pragma comment(lib, "ws2_32.lib")

void setHints()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void sendMessages() {
	std::string username;
	std::cout << "Enter your username: ";
	std::cin >> username;
	send(connectSocket, username.c_str(), username.length(), 0);
	std::string message;
	while (true) {
		std::cin >> message;
		if (send(connectSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
			std::cout << "Error occured when seding message to server.";
		}
	}
}

void receiveMessageFromServer()
{
	char receivebuffer[256];
	while (true) {
		ZeroMemory(receivebuffer, 256);
		if (recv(connectSocket, receivebuffer, 256, 0) != SOCKET_ERROR)
		{
			std::cout << receivebuffer;
		}
	}
}

void clear(const std::string& message, addrinfo* info, SOCKET* socket)
{
	std::cout << message << "\n";
	if (info)
		freeaddrinfo(info);
	if (socket)
		closesocket(*socket);

	WSACleanup();
}

int main() {
	int res = WSAStartup(MAKEWORD(2, 2), &data);
	if (res != 0)
	{
		std::cout << "Startup failed with code " << res << '\n';
		return 1;
	}

	setHints();

	res = getaddrinfo("127.0.0.1", "7777", &hints, &serverInfo);
	if (res != 0)
	{
		clear("getaddrinfo error. Code : " + std::to_string(res) + '\n');
		return false;
	}

	connectSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if (connectSocket == INVALID_SOCKET)
	{
		clear("Connection ConnectSocket failed.\n", serverInfo);
		return 1;
	}

	res = connect(connectSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);
	if (res == SOCKET_ERROR)
	{
		clear("Unable connect to server.\n", serverInfo, &connectSocket);
		return false;
	}

	std::cout << "Connected to server. Write your messages!\n";
	
	std::thread sendMessagesThread(&sendMessages);
	std::thread receiveMessagesThread(&receiveMessageFromServer);

	sendMessagesThread.join();
	receiveMessagesThread.join();

	clear("", serverInfo, &connectSocket);
	WSACleanup();
}