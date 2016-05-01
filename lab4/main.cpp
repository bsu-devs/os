#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include "dll.h" 

#define WM_ATTACHED 13
#define WM_DETACHED 14
#define ID_LABEL 15

using namespace std;

HWND label;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int ss) {
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hI;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "WindowClass";
	if (!RegisterClass(&wc)) return FALSE;

	HWND window = CreateWindow("WindowClass", "WINAPI Lab4 App", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, NULL, NULL, hI, NULL);
	label = CreateWindow("static", "ST_U", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, 0, 300, 100, window, (HMENU)(ID_LABEL), (HINSTANCE)GetWindowLong(window, GWL_HINSTANCE), NULL);
	if (!window) return FALSE;
	ShowWindow(window, ss);
	UpdateWindow(window);

	string s = "A window was created. Current count is " + to_string(windowCount);
	SetWindowText(label, s.c_str());

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	} 
	return msg.wParam; 
}

LRESULT CALLBACK WindowProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	string s;
	switch (msg) {
		case WM_CREATE:
			windowCount = windowCount + 1;
			SendMessage(HWND_BROADCAST, WM_ATTACHED, NULL, NULL);
			return 0;
		case WM_ATTACHED:
			s = "A window was attached. Current count is " + to_string(windowCount);
			SetWindowText(label, s.c_str());
			break;
		case WM_DETACHED:
			s = "A window was detached. Current count is " + to_string(windowCount);
			SetWindowText(label, s.c_str());
			break;
		case WM_DESTROY:
			windowCount = windowCount - 1;
			SendMessage(HWND_BROADCAST, WM_DETACHED, NULL, NULL);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}