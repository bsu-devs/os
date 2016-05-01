#ifndef LIBBSU
#define LIBBSU

#ifdef LIB_EXPORT
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif

extern "C"
{
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
	LIBAPI const char* whoami();
	LIBAPI int timestamp;
	LIBAPI MyObject* object;
}

#endif