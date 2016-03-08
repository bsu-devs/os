#ifndef LIBBSU
#define LIBBSU

#ifdef LIB_EXPORT
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif

#include <Windows.h>

extern "C"
{
	LIBAPI getContributor(int a) {
		HINSTANCE hI = GetModuleHandler(NULL);
		TCHAR string[160];
		switch (a) {
			case 0:
				LoadString(hI, CONTRIBUTORS_0, string, sizeof(string) / sizeof(TCHAR)); 
				break;
			case 1:
				LoadString(hI, CONTRIBUTORS_1, string, sizeof(string) / sizeof(TCHAR)); 
				break;
			case 2:
				LoadString(hI, CONTRIBUTORS_3, string, sizeof(string) / sizeof(TCHAR)); 
				break;
			default:
				string = L"Choose id in [0,1,2] because there are only 3 contributors!";
				break;
		}
		return string;
	}
}

#endif