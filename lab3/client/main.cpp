#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

#define ID_SHOW_CONTRIBUTOR_0 1
#define ID_SHOW_CONTRIBUTOR_1 2
#define ID_SHOW_CONTRIBUTOR_2 3

HMODULE hResourceLib = NULL;

int WINAPI WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int ss) {
	hResourceLib = LoadLibraryEx("../dll-exports-resource/Debug/lab-3-resource-dll.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (!hResourceLib) throw GetLastError();

	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hI;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "WindowClass";
	if (!RegisterClass(&wc)) return FALSE;

	HWND window = CreateWindow("WindowClass", "WINAPI Lab3 App", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, NULL, NULL, hI, NULL);
	if (!window) return FALSE;
	ShowWindow(window, ss);
	UpdateWindow(window);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	FreeLibrary(hResourceLib);
	return msg.wParam; 
}

LRESULT CALLBACK WindowProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_CREATE:
			CreateWindow("button","Show 1st contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				0, 0, 300, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_0, NULL, NULL);
			CreateWindow("button","Show 2nd contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				0, 20, 300, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_1, NULL, NULL);
			CreateWindow("button","Show 3rd contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				0, 40, 300, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_2, NULL, NULL);
			return 0;
		case WM_COMMAND:
			if (HIWORD(wp) != 0) return 0;
			TCHAR p[160];
			switch (LOWORD(wp)) {
				case ID_SHOW_CONTRIBUTOR_0:
					LoadString(hResourceLib, 0, p, sizeof(p) / sizeof(TCHAR));
					break;
				case ID_SHOW_CONTRIBUTOR_1:
					LoadString(hResourceLib, 1, p, sizeof(p) / sizeof(TCHAR));
					break;
				case ID_SHOW_CONTRIBUTOR_2:
					LoadString(hResourceLib, 2, p, sizeof(p) / sizeof(TCHAR));
					break;
				default:
					return 0;
			}
			MessageBox(hw, p, "MessageBox", MB_OK);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}