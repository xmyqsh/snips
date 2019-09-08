#include "Test.h"
#include <cstdio>
#include <cassert>

template<typename _T> void PrintFieldInfo()
{
	printf("struct size : %d \n", sizeof(_T));
	printf("fieldinfo size : %d \n", _T::fieldinfo.size());
	printf("struct layout : \n");
	for (auto iter = _T::fieldinfo.begin(); iter != _T::fieldinfo.end(); iter++)
  {
		printf("%s, %s, %d \n", (*iter).name.c_str(), (*iter).type.c_str(), (*iter).offset);
	}
}

int main()
{
 	PrintFieldInfo<Test>();

	Test test;
	ParaseToType<Test>().Parase(test, "a=5;b=6.0f;c=766666666hhhhhgfdd");
	printf("a = %d, b = %f, c = %s \n", test.a, test.b, test.c.c_str());
  return 0;
}
