#ifndef METADATA_H
#define METADATA_H


#include <cassert>
#include <cstring>


#include <vector>
#include <string>
using namespace std;

namespace {

/*
 * 成员变量的元数据
 */
struct FieldMetadata
{
	// 成员变量的名称
	string name;

	// 成员变量的类型
	string type;

	// 成员变量的地址
	size_t offset;

	FieldMetadata(string name, string type, size_t offset)
	{
		this->name = name;
		this->type = type;
		this->offset = offset;
	}
};


/*
 * 声明结构体类型
 */
#define Declare_Struct(class_type) \
private: \
 \
typedef class_type this_class; \
 \
template<int N> class Init_I \
{ \
public: \
	Init_I(vector<FieldMetadata>& metas) \
	{} \
}; \


/*
 * 定义结构体变量
 */
#define Define_Field(var_index, var_type, var_name) \
public: \
 \
var_type var_name; \
 \
private: \
 \
template<> class Init_I<var_index> \
{ \
public: \
	Init_I(vector<FieldMetadata>& metas) \
	{ \
		FieldMetadata fmd(#var_name, typeid(var_type).name(), offsetof(this_class, var_name)); \
		metas.insert(metas.begin(), fmd); \
	} \
}; \


/*
 * 定义结构体元数据
 */
#define Define_Metadata(var_count) \
public: \
 \
static vector<FieldMetadata> fieldinfo; \
 \
private: \
 \
template<int N> class CallInits \
{ \
public: \
	CallInits(vector<FieldMetadata>& metas) \
	{ \
		Init_I<N> in(metas); \
		CallInits<N-1> ci(metas); \
	} \
}; \
 \
template<> class CallInits<1> \
{ \
public: \
	CallInits(vector<FieldMetadata>& metas) \
	{ \
		Init_I<1> in(metas); \
	} \
}; \
 \
static vector<FieldMetadata> Init() \
{ \
	vector<FieldMetadata> fmd; \
	CallInits<var_count> ci(fmd); \
	return fmd; \
} \


/*
 * 实现结构体类型
 */
#define Implement_Struct(class_type) \
vector<FieldMetadata> class_type::fieldinfo = class_type::Init(); \


typedef unsigned char byte;


/*
 * 解析字符串到类型
 */
template<typename _T>
class ParaseToType
{
private:

	/*
	 * 内存值拷贝
	 */
	void CopyValueOnMemory(byte* memvalue, string type, string strvalue)
	{
		int off = strvalue.find('=');
		string name = strvalue.substr(0, off);
		string value = strvalue.substr(off + 1);

		if (type.compare(typeid(int).name()) == 0)
		{
			int vl = atoi(value.c_str());
			memcpy(memvalue, &vl, sizeof(int));
		}
		else if (type.compare(typeid(double).name()) == 0)
		{
			double vl = atof(value.c_str());
			memcpy(memvalue, &vl, sizeof(double));
		}
		else if (type.compare(typeid(string).name()) == 0)
		{
			string* strmem = (string*)memvalue;
			strmem->append(value);
		}
		else
		{
			/*
			 * Only support the following types
			 * int, double, std::string
			 */
			assert(false);
		}
	}

public:

	/*
	 * 字符串的格式:"a=5;b=6.0f;c=766666666hhhhhgfdd"
	 */
	bool Parase(_T& t, string strvalue)
	{
		int stroffset = 0;

		for (auto iter = _T::fieldinfo.begin(); iter != _T::fieldinfo.end(); iter++)
		{
			int newoffset = strvalue.find(';', stroffset);
			string ty = strvalue.substr(stroffset, newoffset - stroffset);

			byte* th = (((byte*)&t) + (*iter).offset);
			CopyValueOnMemory(th, (*iter).type, ty);

			stroffset = newoffset + 1;
		}

		return true;
	}

};

} // namespace
#endif /*METADATA_H*/
