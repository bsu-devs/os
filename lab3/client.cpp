// WIN32 App
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
HMODULE hFunctionLib = NULL;

int WINAPI WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int ss) {
	hFunctionLib = LoadLibraryA("dll-exports-function/lib.dll");
	if (!hFunctionLib) throw GetLastError();
	hResourceLib = LoadLibraryEx("dll-exports-resource/lib.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (!hResourceLib) throw GetLastError();

	// Getting random contributor with dll's function to know who is the best @dev
 	srand(time(NULL));
	void (*getContributor)();
	getContributor = (void (*)()) GetProcAdress(hFunctionLib, "getContributor");
	MessageBox(hw, "Do you know who is the best contributor EVER!?!?!?", "MessageBox", MB_OK);
	MessageBox(hw, getContributor(srand() % 3), "MessageBox", MB_OK);

	// was u thinking u'll never see WINAPI more? No such luck!! :)
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

	HWND window = CreateWindow("WindowClass", "WINAPI Lab3 App", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hI, NULL);
	if (!window) return FALSE;
	ShowWindow(window, ss);
	UpdateWindow(window);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	FreeLibrary(hResourceLib);
	FreeLibrary(hFunctionLib);
	return msg.wParam; 
}

LRESULT CALLBACK WindowProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_CREATE:
			CreateWindow("button","Show 1st contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				5, 5, 100, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_0, NULL, NULL);
			CreateWindow("button","Show 2nd contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				5, 110, 100, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_1, NULL, NULL);
			CreateWindow("button","Show 3rd contributor", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
				5, 215, 100, 20, hw, (HMENU)ID_SHOW_CONTRIBUTOR_2, NULL, NULL);
			return 0;
		case WM_COMMAND:
			if (HIWORD(wp) != 0) return 0;
			if ((LOWORD(wp) == ID_SHOW_CONTRIBUTOR_0)) {
			TCHAR p[160];
			switch (LOWORD(wp)) {
				case ID_SHOW_CONTRIBUTOR_0:
					// im not sure how to load from here.. 2 possible solutions are:
					// 1) LoadString(hResourceLib, CONTRIBUTORS_0, p, sizeof(p) / sizeof(TCHAR)); 
					// + add #define headers
					// 2) LoadString(hResourceLib, "CONTRIBUTORS_0", p, sizeof(p) / sizeof(TCHAR));
					LoadString(hResourceLib, "CONTRIBUTORS_0", p, sizeof(p) / sizeof(TCHAR));
					break;
				case ID_SHOW_CONTRIBUTOR_1:
					LoadString(hResourceLib, "CONTRIBUTORS_1", p, sizeof(p) / sizeof(TCHAR));
					break;
				case ID_SHOW_CONTRIBUTOR_2:
					LoadString(hResourceLib, "CONTRIBUTORS_2", p, sizeof(p) / sizeof(TCHAR));
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