#ifndef CPPLUA_UTILITIES_LUASTACK_H
#define CPPLUA_UTILITIES_LUASTACK_H

#include "../scriptlua.h"

extern "C"
{
	#include <lauxlib.h>
}

#include <string>

//////
// Open questions:
// - Should we consider a char as a string of only one character ? Or as an integer ?

namespace CppLua
{

template <class T>
struct LuaStack;

// lua state*
// luaCFunction

// int
template <>
struct LuaStack <int>
{
	static void Push(lua_State* iL, int iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static int Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

template <>
struct LuaStack <const int&>
{
	static void Push(lua_State* iL, const int& iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static int Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

// unsigned int
template <>
struct LuaStack <unsigned int>
{
	static void Push(lua_State* iL, int iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned int Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned int>(luaL_checkunsigned(iL, iIndex));
	}
};

template <>
struct LuaStack <const unsigned int&>
{
	static void Push(lua_State* iL, const unsigned int& iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned int Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned int>(luaL_checkunsigned(iL, iIndex));
	}
};

// char
template <>
struct LuaStack <char>
{
	static void Push(lua_State* iL, char iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static char Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

template <>
struct LuaStack <const char&>
{
	static void Push(lua_State* iL, const char& iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static char Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

// unsigned char
template <>
struct LuaStack <unsigned char>
{
	static void Push(lua_State* iL, unsigned char iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned char Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned char>(luaL_checkunsigned(iL, iIndex));
	}
};

template <>
struct LuaStack <const unsigned char&>
{
	static void Push(lua_State* iL, const unsigned char& iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned char Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned char>(luaL_checkunsigned(iL, iIndex));
	}
};

// const char*
template <>
struct LuaStack <const char*>
{
	static void Push(lua_State* iL, const char* iValue)
	{
		if (iValue != 0)
		{
			lua_pushstring(iL, iValue);
		}
		else
		{
			lua_pushnil(iL);
		}
	}

	static const char* Get(lua_State* iL, int iIndex)
	{
		return lua_isnil(iL, iIndex) ? 0 : luaL_checkstring(iL, iIndex);
	}
};

// short
template <>
struct LuaStack <short>
{
	static void Push(lua_State* iL, short iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static short Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

template <>
struct LuaStack <const short&>
{
	static void Push(lua_State* iL, const short& iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static short Get(lua_State* iL, int iIndex)
	{
		return luaL_checkint(iL, iIndex);
	}
};

// unsigned short
template <>
struct LuaStack <unsigned short>
{
	static void Push(lua_State* iL, unsigned short iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned short Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned short>(luaL_checkunsigned(iL, iIndex));
	}
};

template <>
struct LuaStack <const unsigned short&>
{
	static void Push(lua_State* iL, const unsigned short& iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned short Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned short>(luaL_checkunsigned(iL, iIndex));
	}
};

// long
template <>
struct LuaStack <long>
{
	static void Push(lua_State* iL, long iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static long Get(lua_State* iL, int iIndex)
	{
		return luaL_checklong(iL, iIndex);
	}
};

template <>
struct LuaStack <const long&>
{
	static void Push(lua_State* iL, const long& iValue)
	{
		lua_pushinteger(iL, iValue);
	}

	static long Get(lua_State* iL, int iIndex)
	{
		return luaL_checklong(iL, iIndex);
	}
};

// unsigned long
template <>
struct LuaStack <unsigned long>
{
	static void Push(lua_State* iL, unsigned long iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned long Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned long>(luaL_checkunsigned(iL, iIndex));
	}
};

template <>
struct LuaStack <const unsigned long&>
{
	static void Push(lua_State* iL, const unsigned long& iValue)
	{
		lua_pushunsigned(iL, iValue);
	}

	static unsigned long Get(lua_State* iL, int iIndex)
	{
		return static_cast<unsigned long>(luaL_checkunsigned(iL, iIndex));
	}
};

// float
template <>
struct LuaStack <float>
{
	static void Push(lua_State* iL, float iValue)
	{
		lua_pushnumber(iL, iValue);
	}

	static float Get(lua_State* iL, int iIndex)
	{
		return static_cast<float>(luaL_checknumber(iL, iIndex));
	}
};

template <>
struct LuaStack <const float&>
{
	static void Push(lua_State* iL, const float& iValue)
	{
		lua_pushnumber(iL, iValue);
	}

	static float Get(lua_State* iL, int iIndex)
	{
		return static_cast<float>(luaL_checknumber(iL, iIndex));
	}
};

// double
template <>
struct LuaStack <double>
{
	static void Push(lua_State* iL, double iValue)
	{
		lua_pushnumber(iL, iValue);
	}

	static double Get(lua_State* iL, int iIndex)
	{
		return static_cast<double>(luaL_checknumber(iL, iIndex));
	}
};

template <>
struct LuaStack <const double&>
{
	static void Push(lua_State* iL, const double& iValue)
	{
		lua_pushnumber(iL, iValue);
	}

	static double Get(lua_State* iL, int iIndex)
	{
		return static_cast<double>(luaL_checknumber(iL, iIndex));
	}
};

// bool
template <>
struct LuaStack <bool>
{
	static void Push(lua_State* iL, bool iValue)
	{
		lua_pushboolean(iL, iValue);
	}

	static bool Get(lua_State* iL, int iIndex)
	{
		return lua_toboolean(iL, iIndex) == 1;
	}
};

template <>
struct LuaStack <const bool&>
{
	static void Push(lua_State* iL, const bool& iValue)
	{
		lua_pushboolean(iL, iValue);
	}

	static bool Get(lua_State* iL, int iIndex)
	{
		return lua_toboolean(iL, iIndex) == 1;
	}
};

// std::string
template <>
struct LuaStack <std::string>
{
	static void Push(lua_State* iL, std::string iValue)
	{
		lua_pushlstring(iL, iValue.c_str(), iValue.size());
	}

	static std::string Get(lua_State* iL, int iIndex)
	{
		size_t len;
		const char* str = luaL_checklstring(iL, iIndex, &len);
		return std::string(str, len);
	}
};

template <>
struct LuaStack <const std::string&>
{
	static void Push(lua_State* iL, const std::string& iValue)
	{
		lua_pushlstring(iL, iValue.c_str(), iValue.size());
	}

	static std::string Get(lua_State* iL, int iIndex)
	{
		size_t len;
		const char* str = luaL_checklstring(iL, iIndex, &len);
		return std::string(str, len);
	}
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_LUASTACK_H
