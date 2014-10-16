#ifndef CPPLUA_UTILITIES_CONSTRUCTORINVOKER_H_
#define CPPLUA_UTILITIES_CONSTRUCTORINVOKER_H_

#include "arglist.h"

namespace CppLua
{

template <class T, class L>
struct ConstructorInvoker {};

template <class T>
struct ConstructorInvoker <T, void (*)()>
{
	typedef void Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2>)
	{
		return new (iMemory) T();
	}
};

template <class T, class ARG1>
struct ConstructorInvoker <T, void (*)(ARG1)>
{
	typedef TypeList<ARG1> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.hd);
	}
};

template <class T, class ARG1, class ARG2>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2)>
{
	typedef TypeList<ARG1, TypeList<ARG2>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3, class ARG4>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3, ARG4)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4>>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3, ARG4, ARG5)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5>>>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6>>>>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6, TypeList<ARG7>>>>>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
struct ConstructorInvoker <T, void (*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8)>
{
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6, TypeList<ARG7, TypeList<ARG8>>>>>>>> Arguments;

	static T* Call(void* iMemory, ArgList<Arguments, 2> iArgs)
	{
		return new (iMemory) T(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_CONSTRUCTORINVOKER_H_
