#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>

namespace Pixel
{
	namespace Network
	{
		extern WSADATA wsaData;

		// 初始化
		bool Init();

		// IP协议
		enum IPProtocol
		{
			IPV4,
			IPV6
		};

		// 传输协议
		enum TransportProtocol
		{
			TCP,
			UDP
		};

		// 服务器
		class Server
		{
		public:
			Server(IPProtocol ipProtocol, TransportProtocol transportProtocol, unsigned short port);
			// 初始化
			bool Init();
			// 监听
			bool Listen();
			// 接受连接
			SOCKET Accept();
			// 接收消息
			std::string Read(SOCKET clientSocket);
			// 发送消息
			bool Send(SOCKET clientSocket, std::string content);
			// 关闭服务器
			bool Close(SOCKET clientSocket);
		private:
			IPProtocol			_ipProtocol;
			TransportProtocol	_transportProtocol;
			unsigned short		_port;
			addrinfo			_hints;
			SOCKET				_listenSocket;
		};
	}
}