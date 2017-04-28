#pragma once
#include <Windows.h>
#include <stdio.h>
class ServerSocket
{
public:
	ServerSocket();
	long log_bin;
	void Init(int port);
	void ListenAndAccept();
	void Receive(char* buffer, int size);
	void Send(char* message, int size);
private:
	char raw_msg[200];
	WSAData winsock_data;
	SOCKADDR_IN addr;
	WORD winsock_version;
	int addr_size;
	SOCKET client_sock;
	SOCKET listen_sock;
};

