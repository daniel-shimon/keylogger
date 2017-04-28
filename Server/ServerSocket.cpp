#include <tchar.h>
#include "ServerSocket.h"
#pragma comment(lib, "Ws2_32.lib")
#define SCK_VERSION2 0x0202


ServerSocket::ServerSocket()
{
	winsock_version = MAKEWORD(2, 1);
	addr_size = sizeof(addr);
}

void ServerSocket::Init(int port)
{
	log_bin = WSAStartup(winsock_version, &winsock_data);
	log_bin = WSAGetLastError();
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	log_bin = WSAGetLastError();
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
}

void ServerSocket::ListenAndAccept()
{
	log_bin = bind(listen_sock, (SOCKADDR*)&addr, addr_size);
	log_bin = listen(listen_sock, 1);
	client_sock = accept(listen_sock, NULL, NULL);
}

void ServerSocket::Receive(char* buffer, int size)
{
	log_bin = recv(client_sock, buffer, size, 0);
}

void ServerSocket::Send(char* message, int size)
{
	log_bin = send(client_sock, message, size, 0);
	log_bin = WSAGetLastError();
}