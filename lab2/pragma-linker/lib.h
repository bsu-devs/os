#ifndef LIBBSU
#define LIBBSU

#ifdef LIB_EXPORT
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif

#pragma comment(linker, "/EXPORT:sum=?sum@@YAHHH@Z")
#pragma comment(linker, "/EXPORT:whoami=?whoami@@YAPADXZ")
#pragma comment(linker, "/EXPORT:timestamp=?timestamp@@3HA")
#pragma comment(linker, "/EXPORT:object=?object@@3PAVMyObject@@A")
#pragma comment(linker, "/EXPORT:createObject=?createObject@@YAPAVIMyObject@@AAPBD@Z")
class IMyObject {
public:
	virtual char* getName() = 0;
	virtual void setName(const char*&) = 0;
	//virtual ~IMyObject() = 0;
};

class MyObject : public IMyObject {
private:
	char* name;
public:
	MyObject(const char*&);
	char* getName();
	void setName(const char*&);
	~MyObject();
};
LIBAPI IMyObject* createObject(const char*& s);

LIBAPI int sum(int a, int b);
LIBAPI char* whoami(void);
LIBAPI int timestamp;
LIBAPI MyObject* object;

#endif
