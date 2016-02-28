#ifndef LIBBSU
#define LIBBSU

#ifdef LIB_EXPORT
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif

#pragma comment(linker, "/EXPORT:sum=<paste mangled name from dll's dumpbin>")
#pragma comment(linker, "/EXPORT:whoami=<paste mangled name from dll's dumpbin>")
#pragma comment(linker, "/EXPORT:timestamp=<paste mangled name from dll's dumpbin>")
#pragma comment(linker, "/EXPORT:object=<paste mangled name from dll's dumpbin>")

class LIBAPI MyObject {
private:
	char* name;
public:
	MyObject(const char&);
	char* getName();
	void setName(char*);
	~MyObject();
};

LIBAPI int sum(int a, int b);
LIBAPI const char& whoami(void);
LIBAPI time_t timestamp;
LIBAPI MyObject* object;

#endif