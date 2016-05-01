#ifndef LIBBSU
#define LIBBSU


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
IMyObject* createObject(const char*& s);
int sum(int a, int b);
char* whoami(void);
time_t timestamp = 0;
MyObject* object = NULL;

#endif
