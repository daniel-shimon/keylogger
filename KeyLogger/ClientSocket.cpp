#include "ClientSocket.h"
#pragma comment(lib, "Ws2_32.lib")
#define SCK_VERSION2 0x0202
// #pragma comment(lib, "libws2_32.a")
// #include <winsock2.h>


ClientSocket::ClientSocket()
{
	winsock_version = MAKEWORD(2, 1);
	addr_size = sizeof(addr);
}

void ClientSocket::Init()
{
	log_bin = WSAStartup(winsock_version, &winsock_data);
	log_bin = WSAGetLastError();
	sock = socket(AF_INET, SOCK_STREAM, 0);
	log_bin = WSAGetLastError();
}

void ClientSocket::Connect(const char* ip_address, int port)
{
	addr.sin_addr.s_addr = inet_addr(ip_address);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	log_bin = connect(sock, (SOCKADDR*)&addr, addr_size);
	log_bin = WSAGetLastError();
}

void ClientSocket::Receive(char* buffer)
{
	log_bin = recv(sock, buffer, sizeof(buffer), 0);
}

void ClientSocket::Send(char* message, int size)
{
	log_bin = send(sock, message, size, 0);
	log_bin = WSAGetLastError();
}

void ClientSocket::Close()
{

}
