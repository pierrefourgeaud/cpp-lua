#ifndef CPPLUA_UTILITIES_METHODINVOKER_H
#define CPPLUA_UTILITIES_METHODINVOKER_H

#include "../scriptlua.h"
#include "arglist.h"

namespace CppLua
{

// default
template <class Meth, class MethPtr = Meth>
struct MethodInvoker {};


template <class ObjT, class RetT, class MethPtr>
struct MethodInvoker <RetT (ObjT::*) (), MethPtr>
{
	typedef RetT ReturnType;
	typedef void Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2>)
	{
		return (iObj->*iMethPtr)();
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1>
struct MethodInvoker <RetT (ObjT::*) (ARG1), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(iArgs.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(iArgs.m_Head, iArgs.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3, class ARG4>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3, ARG4), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4>>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(
			iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3, ARG4, ARG5), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5>>>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(
			iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6>>>>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(
			iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6, TypeList<ARG7>>>>>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(
			iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

template <class ObjT, class RetT, class MethPtr, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
struct MethodInvoker <RetT (ObjT::*) (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8), MethPtr>
{
	typedef RetT ReturnType;
	typedef TypeList<ARG1, TypeList<ARG2, TypeList<ARG3, TypeList<ARG4, TypeList<ARG5, TypeList<ARG6, TypeList<ARG7, TypeList<ARG8>>>>>>>> Arguments;

	static ReturnType Call(ObjT* iObj, MethPtr iMethPtr, ArgList<Arguments, 2> iArgs)
	{
		return (iObj->*iMethPtr)(
			iArgs.m_Head, iArgs.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head,
			iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head, iArgs.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Tail.m_Head);
	}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_METHODINVOKER_H
