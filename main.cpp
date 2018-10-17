#include <iostream>


typedef const type_info TypeDescriptor;
typedef unsigned long DWORD;
struct PMD {
	ptrdiff_t mdisp; //vftable offset	
	ptrdiff_t pdisp; //vftable offset	
	ptrdiff_t vdisp; //vftable offset(for virtual base class)
};
typedef const struct _s_RTTIBaseClassDescriptor {
	TypeDescriptor                  *pTypeDescriptor;
	DWORD                           numContainedBases;
	PMD                             where;
	DWORD                           attributes;
} _RTTIBaseClassDescriptor;
typedef const struct  _s_RTTIBaseClassArray
{
	_RTTIBaseClassDescriptor* arrayOfBaseClassDescriptors[];
}_RTTIBaseClassArray;

typedef const struct _s_RTTIClassHierarchyDescriptor
{
	DWORD                           signature;
	DWORD                           attributes;
	DWORD                           numBaseClasses;
	_RTTIBaseClassArray             *pBaseClassArray;
}_RTTIClassHierarchyDescriptor;

typedef const struct _s_RTTICompleteObjectLocator {

	DWORD signature;
	DWORD offset;			 //vftbl相对this的偏移	
	DWORD cdOffset;		 //constructor displacement 	
	TypeDescriptor *pTypeDescriptor;
	_RTTIClassHierarchyDescriptor   *pClassDescriptor;
}_RTTICompleteObjectLocator;

class Base
{
public:
	virtual void show()
	{

	}
};
class Top
{
public:
	virtual void top_show()
	{

	}
};
class Left :virtual public Base
{
public:
	Left()
	{
		do_call();
		//auto completelocalptr = (_RTTICompleteObjectLocator*)((*(void***)bptr)[-1]);
		//std::cout << completelocalptr->offset << std::endl;   //16
		//std::cout << completelocalptr->cdOffset << std::endl;

	}
	virtual void show()
	{
		//std::cout << "left show" << std::endl;
	}
	void do_call()
	{
		Base* bptr = this;
		std::cout << dynamic_cast<Left*>(bptr)->m_left << std::endl;

		auto completelocalptr = (_RTTICompleteObjectLocator*)((*(void***)bptr)[-1]);
		std::cout << completelocalptr->offset << std::endl;   //16
		auto pptr = completelocalptr->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
		for (int i = 0; i < completelocalptr->pClassDescriptor->numBaseClasses; i++)
		{
			std::cout<<(*pptr)->pTypeDescriptor->name()<<std::endl;
			pptr++;
		}
		std::cout << "vdisp===" << *(long*)(((void***)bptr) - 1) << std::endl;
		show();
	}
	//virtual void left_show()
	//{

	//}
	int m_left = 1024;
};
class Test :public Top,public Left
{
public:
	int m_test;
	//virtual void test_show()
	//{

	//}
};

int main()
{
	Test *t = new Test();

	//Base* bptr = t;
	//auto completelocalptr = (_RTTICompleteObjectLocator*)((*(void***)bptr)[-1]);
	//std::cout << completelocalptr->offset << std::endl;   //16
	//std::cout << completelocalptr->cdOffset << std::endl;

	//void** ptr = *(void***)t;
	//void** ptr = *(((void***)t)+1);
	//long vfoffset = *((long*)ptr);
	//std::cout << vfoffset << std::endl;
	//long vbaseclassoffset = *((long*)(ptr+1));
	//std::cout << vbaseclassoffset << std::endl;
	std::cin.get();
}
