#ifndef LIBBSU
#define LIBBSU

#ifdef LIB_EXPORT
#define LIBAPI __declspec(dllexport)
#else
#define LIBAPI __declspec(dllimport)
#endif

extern "C"
{
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
}

#endif