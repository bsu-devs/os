#ifndef LIBBSU
#define LIBBSU

#define DECLDIR __declspec(dllexport)

extern "C"
{
    DECLDIR int sum(int a, int b);
    DECLDIR void printCopyright(void);
    DECLDIR void showCopyright(void);
}

#endif