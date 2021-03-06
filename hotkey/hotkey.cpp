#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <atlstr.h>
#define _WIN32_WINNT 0x050
#define KEYB_NUM9 105
using namespace std;
int altDown = 0;
int test = 0;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
			break;
		case WM_SYSKEYDOWN:
			printf("%02x", p->vkCode);
			cout << " vk" << endl;
			printf("%02x", p->scanCode);
			cout << " sC" << endl;
			printf("%02x", p->flags);
			cout << " flag" << endl;
			printf("%02x", p->dwExtraInfo);
			cout << " extra" << altDown << endl;
			if (fEatKeystroke = (p->vkCode == 0xa4)) {     //redirect a to b
				if (altDown == 0)
				{
					altDown = 1;
				}
			}
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (fEatKeystroke = (p->vkCode == 0xa4) && p->flags == 0x80) {    
				keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0); // Alt Release
				cout << "setting false" << endl;
				altDown = 0;
			}
			else
			{

			}
			//printf("%02x", p->vkCode);
			//cout << " vk" << endl;
			//printf("%02x", p->scanCode);
			//cout << " sC" << endl;
			//printf("%02x", p->flags);
			//cout << " flag" << endl;
			//printf("%02x", p->dwExtraInfo);
			//cout << " extra" << altDown << endl;
			if (altDown == 1)
			{
				//printf("%02x", p->flags);
				if (p->flags == 0xa0)
				{
					if (fEatKeystroke = (p->vkCode == 0x41)) {     //redirect a to b
						keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0); // Alt Release
						INPUT tabinput[2];
						tabinput[0].type = INPUT_KEYBOARD;
						tabinput[0].ki.dwFlags = KEYEVENTF_UNICODE;
						tabinput[0].ki.wVk = 0;
						tabinput[0].ki.wScan = 0x00E1; // This is a a with accent mark unicode character
						tabinput[1].type = INPUT_KEYBOARD;
						tabinput[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
						tabinput[1].ki.wVk = 0;
						tabinput[1].ki.wScan = 0x00E1; // This is a a with accent mark unicode character
						SendInput(2, tabinput, sizeof(INPUT));
						test = 0;

					}
					else {
						fEatKeystroke = (p->vkCode == p->vkCode);
					}
				}

			}
			break;
		}
	}
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

int main()
{


	//Sleep(1000 * 3);
	//cout<<'a'<<endl;
	//INPUT tabinput[2];
	//tabinput[0].type = INPUT_KEYBOARD;
	//tabinput[0].ki.dwFlags = KEYEVENTF_UNICODE;
	//tabinput[0].ki.wVk = 0;
	//tabinput[0].ki.wScan = 0x00E1; // This is a a with accent mark unicode character
	//tabinput[1].type = INPUT_KEYBOARD;
	//tabinput[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	//tabinput[1].ki.wVk = 0;
	//tabinput[1].ki.wScan = 0x00E1; // This is a a with accent mark unicode character
	//SendInput(2, tabinput, sizeof(INPUT));
	//getchar();
	// Install the low-level keyboard & mouse hooks
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hhkLowLevelKybd);

	return(0);
}