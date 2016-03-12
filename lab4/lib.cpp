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
  SHAREDBUFFERDLL_API HWND count = 0;
#pragma data_seg()

#pragma comment(linker,"/Section:SharedSection,RWS")