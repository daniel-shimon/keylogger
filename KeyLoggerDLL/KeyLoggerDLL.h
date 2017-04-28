#pragma once
#define DLLExport _declspec(dllexport)
#include <Windows.h>
#include "ClientSocket.h"


extern "C"
{
	HHOOK* kb_hook;
	HHOOK* ms_hook;
	ClientSocket* client;
	int screen_x, screen_y;
	bool shift_on;
	bool ctrl_on;
	bool caps_on;
	void CheckKeyState();
	DLLExport void Init();
	DLLExport void SetHooks(HHOOK* keyboard_hook, HHOOK* mouse_hook);
	DLLExport void SetClient(ClientSocket* client);
	DLLExport LRESULT _stdcall key_proc(int nCode, WPARAM wParam, LPARAM lParam);
	DLLExport LRESULT _stdcall mouse_proc(int nCode, WPARAM wParam, LPARAM lParam);

}
