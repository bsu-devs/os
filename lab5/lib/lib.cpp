#define LAB5_EXPORTS
#include "lib.h"
#pragma data_seg(".shared")
LIB_API char str[500] = "";
#pragma data_seg()
#pragma comment(linker,"/Section:.shared,RWS")