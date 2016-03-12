#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include "./lib/lib.h" 

#define ID_LABEL 1

using namespace std;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int ss) {
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

	receiver = window;

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
			CreateWindow("static","", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				5, 5, 100, 20, hw, (HMENU)ID_LABEL, NULL, NULL);
			return 0;
		case WM_COMMAND:
			if (wp == 123 && lp == 456) SetDlgItemText(ID_LABEL, sharedString);
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}