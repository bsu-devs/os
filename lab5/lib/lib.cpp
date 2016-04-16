#ifndef LIBBSU
#define LIBBSU
#include "lib.h"
#pragma data_seg(".shared")
std::wstring sharedString;
#pragma data_seg()
#pragma comment(linker,"/Section:.shared,RWS")
#endif