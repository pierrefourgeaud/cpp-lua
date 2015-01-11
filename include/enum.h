#ifndef CPPLUA_ENUM_H_
#define CPPLUA_ENUM_H_

#include "scriptlua.h"
#include "helpers/luahelper.h"
#include "utilities/fulluserdata.h"
#include "utilities/luastack.h"
#include <string>

extern "C"
{
	#include <lauxlib.h>
}

/* For now, the Enums can only be INTEGERS...
*  Thinking about another solution
*/
namespace CppLua
{

template <class T>
class Enum
{
public:
	Enum(ScriptLua* iScriptLua, const std::string& iName)
		: m_pScriptLua(iScriptLua)
		, m_Name(iName)
	{
		_Initialize();
	}

	virtual ~Enum()
	{
		_Destroy();
	}

	Enum& Value(const std::string& iName, int iValue)
	{
		lua_State* L = m_pScriptLua->GetState();

		RawGetField(L, -1, "__values");
		// new (lua_newuserdata(L, sizeof(T))) T(iValue);
		// pushcclosure
		LuaStack<int>::Push(L, iValue);
		RawSetField(L, -2, iName.c_str());
		lua_pop(L, 1);

		return *this;
	}

private:
	ScriptLua*        m_pScriptLua;
	const std::string m_Name;

	bool _Initialize()
	{
		lua_State* L = m_pScriptLua->GetState();

		// TODO Verification for lua_istable

		RawGetField(L, -1, m_Name.c_str());

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);

			_CreateEnumTable();
		}
		else
		{
			// ?
		}

		return true;
	}

	bool _Destroy()
	{
		return true;
	}

	static int _GetValue(lua_State* iL)
	{
		T* val = FullUserData<T>::Get(iL, 1);

		return 1;
	}

	void _CreateEnumTable()
	{
		lua_State* L = m_pScriptLua->GetState();

		// Create the metatable
		lua_newtable(L);
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setmetatable(L, -3);
		lua_insert(L, -2);
		RawSetField(L, -3, m_Name.c_str());

		/// Prepare the metatable with the correct fields.
		// set __type=m_Name
		lua_pushstring(L, m_Name.c_str());
		RawSetField(L, -2, "__type");
		// set __index=indexMetatable() -> indexing access metamethod
		lua_pushcfunction(L, &Enum::_IndexMetaMethod);
		RawSetField(L, -2, "__index");
		// set __newindex=newIndexMetatable() // indexing assignement metamethod
		lua_pushcfunction(L, &Enum::_NewIndexMetaMethod);
		RawSetField(L, -2, "__newindex");
		// set __propGetter=NewLuaTable
		lua_newtable(L);
		RawSetField(L, -2, "__values");
	}

	// index access metamethod t[k]
	static int _IndexMetaMethod(lua_State* iL)
	{
		int result = 0;

		lua_getmetatable(iL, 1);

		RawGetField(iL, -1, "__values");
		if (lua_istable(iL, -1))
		{
			lua_pushvalue(iL, 2);
			lua_rawget(iL, -2);
			lua_remove(iL, -2);
			if (lua_isnumber(iL, -1))
			{
				result = 1;
			}
			else if (lua_isnil(iL, -1))
			{
				lua_pop(iL, 1);
			}
			else
			{
				lua_pop(iL, 2);
				// TODO throw an exception here
			}
		}
		else
		{
			lua_pop(iL, 2);
			// TODO throw an exception here
		}

		return result;
	}

	// index assignement metamethod t[k]=v
	static int _NewIndexMetaMethod(lua_State* iL)
	{
		return luaL_error(iL,
			"Trying to modify a read-only value '%s'.", lua_tostring(iL, 2));
	}
};

} // namespace CppLua

#endif // !CPPLUA_ENUM_H_
