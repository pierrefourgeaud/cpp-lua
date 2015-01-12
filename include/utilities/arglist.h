#ifndef CPPLUA_UTILITIES_ARGLIST_H_
#define CPPLUA_UTILITIES_ARGLIST_H_

#include "../scriptlua.h"
#include "luastack.h"
#include <type_traits>

namespace CppLua
{

// Just the list of types for the arguments
template <typename Head, typename Tail = void>
struct TypeList
{};

template <typename List>
struct TypeListValues
{};

template <typename Head, typename Tail>
struct TypeListValues <TypeList <Head, Tail>>
{
	Head                  m_Head;
	TypeListValues <Tail> m_Tail;

	TypeListValues(Head iHead, const TypeListValues<Tail>& iTail)
		: m_Head(iHead)
		, m_Tail(iTail)
	{}
};

template <typename Head, typename Tail>
struct TypeListValues <TypeList <Head&, Tail>>
{
	Head                  m_Head;
	TypeListValues <Tail> m_Tail;

	TypeListValues(Head& iHead, const TypeListValues<Tail>& iTail)
		: m_Head(iHead)
		, m_Tail(iTail)
	{}
};

template <typename Head, typename Tail>
struct TypeListValues <TypeList <const Head&, Tail>>
{
	Head                  m_Head;
	TypeListValues <Tail> m_Tail;

	TypeListValues(const Head& iHead, const TypeListValues<Tail>& iTail)
		: m_Head(iHead)
		, m_Tail(iTail)
	{}
};

template <typename T, bool IsEnum>
struct Type
{
	static T Get(lua_State* iL, int iIndex)
	{
		return LuaStack<T>::Get(iL, iIndex);
	}

	static void Push(lua_State* iL, T iValue)
	{
		LuaStack<T>::Push(iL, iValue);
	}
};

template <typename T>
struct Type <T&, false>
{
	static T& Get(lua_State* iL, int iIndex)
	{
		return LuaStack<T&>::Get(iL, iIndex);
	}

	static void Push(lua_State* iL, T& iValue)
	{
		LuaStack<T&>::Push(iL, iValue);
	}
};

template <typename T>
struct Type <const T&, false>
{
	static const T& Get(lua_State* iL, int iIndex)
	{
		return LuaStack<const T&>::Get(iL, iIndex);
	}

	static void Push(lua_State* iL, const T& iValue)
	{
		LuaStack<const T&>::Push(iL, iValue);
	}
};

template <>
struct Type <const std::string&, false>
{
	static std::string Get(lua_State* iL, int iIndex)
	{
		return LuaStack<const std::string&>::Get(iL, iIndex);
	}

	static void Push(lua_State* iL, const std::string& iValue)
	{
		LuaStack<const std::string&>::Push(iL, iValue);
	}
};

template <typename T>
struct Type <T, true>
{
	static T Get(lua_State* iL, int iIndex)
	{
		return static_cast<T>(LuaStack<int>::Get(iL, iIndex));
	}

	static void Push(lua_State* iL, T iValue)
	{
		LuaStack<int>::Push(iL, static_cast<int>(iValue));
	}
};

template <typename List, int Start = 1>
struct ArgList
{};

template <int StartValue>
struct ArgList <void, StartValue> : public TypeListValues <void>
{
	ArgList(lua_State* iL) {}
};

template <class Head, class Tail, int StartValue>
struct ArgList <TypeList <Head, Tail>, StartValue>
	: public TypeListValues <TypeList <Head, Tail>>
{
	ArgList(lua_State* iL)
		: TypeListValues<TypeList<Head, Tail> >(Type<Head, std::is_enum<Head>::value>::Get(iL, StartValue),
												ArgList<Tail, StartValue + 1>(iL))
	{}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_ARGLIST_H_
