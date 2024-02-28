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

		// ��ʼ��
		bool Init();

		// IPЭ��
		enum IPProtocol
		{
			IPV4,
			IPV6
		};

		// ����Э��
		enum TransportProtocol
		{
			TCP,
			UDP
		};

		// ������
		class Server
		{
		public:
			Server(IPProtocol ipProtocol, TransportProtocol transportProtocol, unsigned short port);
			// ��ʼ��
			bool Init();
			// ����
			bool Listen();
			// ��������
			SOCKET Accept();
			// ������Ϣ
			std::string Read(SOCKET clientSocket);
			// ������Ϣ
			bool Send(SOCKET clientSocket, std::string content);
			// �رշ�����
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