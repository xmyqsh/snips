//StaticAutoRegister.h
template<typename TClass>
struct StaticAutoRegister
{
	StaticAutoRegister()
	{
		Register(TClass::StaticClass());
	}
};
//MyClass.h
class MyClass   // could be lazy singlton
{
    //[...]
};
//MyClass.cpp
#include "StaticAutoRegister.h"
const static StaticAutoRegister<MyClass> AutoRegister;
