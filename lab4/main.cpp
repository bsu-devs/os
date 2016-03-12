#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include "lib.h" 

#define WM_ATTACHED (WM_USER + 0x0001)
#define WM_DETACHED (WM_USER + 0x0002)

using namespace std;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

HWND createWindow(){
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "WindowClass";
	if (!RegisterClass(&wc)) return FALSE;

	HWND window = CreateWindow("WindowClass", "WINAPI Lab4 App", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hI, NULL);
	if (!window) return FALSE;
	ShowWindow(window, ss);
	UpdateWindow(window);
	return window;
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int ss) {
	createWindow();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	return msg.wParam; 
}

LRESULT CALLBACK WindowProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_CREATE:
			InterlockedExchangeAdd((PLONG)&count, 1);
			SendMessage(HWND_BROADCAST, WM_ATTACHED, NULL, NULL);
			return 0;
		case WM_ATTACHED:
			string s = "A window was attached. Current count is " + to_string(count);
			MessageBox(hw, s.c_str(), "MessageBox", MB_OK);
			break;
		case WM_DETACHED:
			string s = "A window was detached. Current count is " + to_string(count);
			MessageBox(hw, s.c_str(), "MessageBox", MB_OK);
			break;
		case WM_COMMAND:
			if (wp == 123 && lp == 456) SetDlgItemText(ID_LABEL, sharedString);
		case WM_DESTROY:
			InterlockedExchangeAdd((PLONG)&count, -1);
			SendMessage(HWND_BROADCAST, WM_DETACHED, NULL, NULL);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}