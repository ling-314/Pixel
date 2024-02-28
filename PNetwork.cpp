#include "PNetwork.hpp"

WSADATA Pixel::Network::wsaData;

bool Pixel::Network::Init()
{
	return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0 ? true : false;
}

Pixel::Network::Server::Server(IPProtocol ipProtocol, TransportProtocol transportProtocol, unsigned short port) :
	_ipProtocol(ipProtocol),
	_transportProtocol(transportProtocol),
	_port(port)
{
}

bool Pixel::Network::Server::Init()
{
	_listenSocket = INVALID_SOCKET;

	addrinfo* result = nullptr;

	ZeroMemory(&_hints, sizeof(_hints));
	_hints.ai_family = _ipProtocol == IPV4 ? AF_INET: AF_INET6;
	_hints.ai_socktype = _transportProtocol == TCP ? SOCK_STREAM : SOCK_DGRAM;
	_hints.ai_protocol = _transportProtocol == TCP ? IPPROTO_TCP : IPPROTO_UDP;
	_hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(nullptr, std::to_string(_port).c_str(), &_hints, &result) != 0)
	{
		WSACleanup();
		return false;
	}

	_listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (_listenSocket == INVALID_SOCKET)
	{
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	if (bind(_listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		freeaddrinfo(result);
		closesocket(_listenSocket);
		WSACleanup();
		return false;
	}

	freeaddrinfo(result);

	return true;
}

bool Pixel::Network::Server::Listen()
{
	if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(_listenSocket);
		WSACleanup();
		return false;
	}

	return true;
}

SOCKET Pixel::Network::Server::Accept()
{
	SOCKET clientSocket = INVALID_SOCKET;

	clientSocket = accept(_listenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		closesocket(_listenSocket);
		WSACleanup();
		return 0;
	}
	closesocket(_listenSocket);
	return clientSocket;
}

std::string Pixel::Network::Server::Read(SOCKET clientSocket)
{
	char buf[65535]; // unsigned short
	recv(clientSocket, buf, 65535, 0);
	return buf;
}

bool Pixel::Network::Server::Send(SOCKET clientSocket, std::string content)
{
	if (send(clientSocket, content.c_str(), content.length(), 0) == SOCKET_ERROR)
	{
		closesocket(clientSocket);
		WSACleanup();
		return false;
	}
	return true;
}

bool Pixel::Network::Server::Close(SOCKET clientSocket)
{
	if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR)
	{
		closesocket(clientSocket);
		WSACleanup();
		return false;
	}
	closesocket(clientSocket);
	WSACleanup();
	return true;
}
