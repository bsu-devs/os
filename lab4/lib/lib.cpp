#include "stdafx.h"
#include "lib.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif
#ifdef _MANAGED
#pragma managed(pop)
#endif

#pragma comment(linker,"/NOENTRY")

#pragma data_seg("SharedSection")
  SHAREDBUFFERDLL_API WCHAR sharedString[500] = {0};
  SHAREDBUFFERDLL_API HWND receiver = NULL;
#pragma data_seg()

#pragma comment(linker,"/Section:SharedSection,RWS")