#ifndef LIBBSU
#define LIBBSU
#include "dll.h"
#pragma comment(linker,"/Section:.shared,RWS")
#pragma data_seg(".shared")
int windowCount = 0;
#pragma data_seg()
#endif