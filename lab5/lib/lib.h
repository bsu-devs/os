#ifdef LAB5_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif

#include <string>
#include <iostream>
#include <Windows.h>

extern "C" LIB_API char str[500];