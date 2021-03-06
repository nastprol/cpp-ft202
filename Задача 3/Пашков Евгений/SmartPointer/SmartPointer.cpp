#include "stdafx.h"
#include "iostream"

using namespace std;

template<typename T>
class SmartPtr
{
	T* ptr;
	size_t* count;

	void initialize_count()
	{
		count = new size_t();
		*count = 1;
	}

	void attach(const SmartPtr<T>& other)
	{
		ptr = other.ptr;
		count = other.count;
		(*count)++;
	}

public:
	SmartPtr() { }

	SmartPtr(const SmartPtr<T>& other) 
	{
		attach(other);
	}

	T* Get()
	{
		return ptr;
	}

	void Set(T* aptr)
	{
		Release();
		ptr = aptr;
		initialize_count();
	}

	void Release()
	{
		if (!ptr)
			return;
		printf("Release %d\n", *count);
		(*count)--;
		if ((*count) == 0)
		{
			delete ptr;
			delete count;
		}
		count = nullptr;
		ptr = nullptr;
	}

	explicit SmartPtr(T* aptr) : ptr(aptr)
	{
		initialize_count();
	}

	T* operator->()
	{
		return Get();
	}

	T& operator* ()
	{
		return *ptr;
	}

	SmartPtr& operator=(const SmartPtr& other)
	{
		Release();
		attach(other);
		return *this;
	}

	~SmartPtr<T>() 
	{
		Release();
	}
};

class TestObject
{
public:
	int X;

	TestObject(const TestObject& other)
	{
		X = other.X;
		printf("New Test Object %d\n", X);
	}

	TestObject()
	{
		X = 0;
		printf("New Test Object 0\n");
	}

	TestObject(int X1) : X(X1)
	{
		printf("New Test Object %d\n", X);
	}

	~TestObject()
	{
		printf("Deleted Test Object %d\n", X);
	}
};

int main()
{
	SmartPtr<TestObject> P1(new TestObject(10));
	SmartPtr<TestObject> P2 = P1;
	cout << P2.Get()->X << endl;
	P1.Release();
	P2.Set(new TestObject(25));
	return 0;
}