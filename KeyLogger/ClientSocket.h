#pragma once
#include <Windows.h>
class ClientSocket
{
public:
	ClientSocket();
	long log_bin;
	void Init();
	void Connect(const char* ip_address, int port);
	void Receive(char* buffer);
	void Send(char* message, int size);
	void Close();
private:
	char raw_msg[200];
	WSAData winsock_data;
	SOCKADDR_IN addr;
	WORD winsock_version;
	int addr_size;
	SOCKET sock;
};

