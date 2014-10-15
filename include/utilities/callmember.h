#ifndef CPPLUA_UTILITIES_CALLMEMBER_H
#define CPPLUA_UTILITIES_CALLMEMBER_H

#include "methodinvoker.h"

/*
* Need to use a trick because Method templates cannot
* be partially specialized.
* The trick is called delegate-to-class.
*/

namespace CppLua
{

template <class MethPtr, typename ReturnType = MethodInvoker<MethPtr>::ReturnType>
struct CallMember
{
	typedef typename MethodInvoker<MethPtr>::ClassType T;

	static int Method(lua_State* iL)
	{
		T* obj = 0;

		// First get the object
		if (!lua_isnil(iL, 1))
		{
			obj = static_cast<T*> (FullUserData<T>::Get(iL, 1)->GetMemoryPtr());
		}

		// Now, get the function ptr
		const MethPtr& methPtr = *static_cast<const MethPtr*>(lua_touserdata(iL, lua_upvalueindex(1)));

		// Finally prepare the call
		ArgList<MethodInvoker<MethPtr>::Arguments, 2> arguments(iL);
		LuaStack<ReturnType>::Push(iL, MethodInvoker<MethPtr>::Call(obj, methPtr, arguments));
		return 1;
	}
};

template <class MethPtr>
struct CallMember <MethPtr, void>
{
	typedef typename MethodInvoker<MethPtr>::ClassType T;

	static int Method(lua_State* iL)
	{
		T* obj = 0;

		// First get the object
		if (!lua_isnil(iL, 1))
		{
			obj = static_cast<T*> (FullUserData<T>::Get(iL, 1)->GetMemoryPtr());
		}

		// Now, get the function ptr
		const MethPtr& methPtr = *static_cast<const MethPtr*>(lua_touserdata(iL, lua_upvalueindex(1)));

		// Finally prepare the call
		ArgList<MethodInvoker<MethPtr>::Arguments, 2> arguments(iL);
		MethodInvoker<MethPtr>::Call(obj, methPtr, arguments);
		return 0;
	}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_CALLMEMBER_H
