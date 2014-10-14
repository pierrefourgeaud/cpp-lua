#ifndef CPPLUA_UTILITIES_ARGLIST_H
#define CPPLUA_UTILITIES_ARGLIST_H

#include "../scriptlua.h"
#include "luastack.h"

namespace CppLua
{

// Just the list of types for the arguments
template <typename Head, typename Tail = void>
struct TypeList
{
};

template <typename List, int Start = 1>
struct ArgList
{
	ArgList(lua_State*) {}
};

template <class Head, class Tail, int StartValue>
struct ArgList <TypeList <Head, Tail>, StartValue>
{
	Head                         m_Head;
	ArgList <Tail, StartValue+1> m_Tail;

	ArgList(const Head& iHead, const ArgList<Tail, StartValue>& iTail)
		: m_Head(iHead)
		, m_Tail(iTail)
	{}

	ArgList(lua_State* iL)
		: m_Head(LuaStack<Head>::Get(iL, StartValue))
		, m_Tail(ArgList<Tail, StartValue + 1>(iL))
	{}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_ARGLIST_H
