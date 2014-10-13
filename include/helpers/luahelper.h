#ifndef CPPLUA_HELPERS_LUAHELPER_H
#define CPPLUA_HELPERS_LUAHELPER_H

extern "C"
{
	#include <lua.h>
}

namespace CppLua
{

inline void RawSetField(lua_State* iL, int iIndex, const char* iKey)
{
	// TODO Make sure that the element at this index is a table
	//      simply by using lua_istable
	int index = lua_absindex(iL, iIndex);   // Convert the passed acceptable iIndex into an absolute index 
	lua_pushstring(iL, iKey);               // Push the string iKey onto the stack
	lua_insert(iL, -2);                     // Move the top element to the given valid index (that is -2)
	lua_rawset(iL, index);                  // t[k]=v where t is the value at the given index, v is the value on
	                                        // top and k the value below the top. Both values are poped afterwards.
}

inline void RawGetField(lua_State* iL, int iIndex, const char* iKey)
{
	// TODO Make sure that the element at this index is a table
	//      simply by using lua_istable
	int index = lua_absindex(iL, iIndex);  // Convert the passed acceptable iIndex into an absolute index
	lua_pushstring(iL, iKey);              // Push the string iKey onto the stack
	lua_rawget(iL, index);                 // t[k] where t is the value at the given index and k the value on top of the stack
}

} // namespace CppLua

#endif // !CPPLUA_HELPERS_LUAHELPER_H
