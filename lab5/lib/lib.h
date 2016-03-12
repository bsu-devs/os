#ifdef LIBAPI_EXPORTS
#define LIBAPI_API __declspec(dllexport)
#else
#define LIBAPI_API __declspec(dllimport)
#endif

extern "C" LIBAPI_API WCHAR sharedString[500];
extern "C" LIBAPI_API HWND receiver;