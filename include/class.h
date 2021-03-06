#ifndef CPPLUA_CLASS_H_
#define CPPLUA_CLASS_H_

#include "scriptlua.h"
#include "helpers/luahelper.h"
#include "utilities/constructorinvoker.h"
#include "utilities/methodinvoker.h"
#include "utilities/callmember.h"
#include "utilities/fulluserdata.h"
#include <string>

namespace CppLua
{

// Class c(l, "MyObject")
// 	.Method("HelloWorld", &MyObject::HelloWorld)
// 	.Property("a", &MyObject::GetA, &MyObject::SetA);

// --- Usage in lua

// local foo = MyObject:new()
// foo:HelloWorld()
// print(foo:a)

// Todo
// - For the destructor of the class, might be better that the
// class is ours and that it exist and everything
// - Maybe secure everything by adding a protection verifying
// that the class has been registered previously.

template <class T>
class Class
{
public:
	static const void* GetIdentityKey()
	{
		static char key;
		return &key;
	}

	Class(ScriptLua* iScriptLua, const std::string& iName)
		: m_pScriptLua(iScriptLua)
		, m_Name(iName)
	{
		_Initialize();
	}

	virtual ~Class()
	{
		_Destroy();
	}

	template <class Ctor>
	Class<T>& Constructor()
	{
		lua_pushcclosure(m_pScriptLua->GetState(), &Class<T>::_ConstructorProxy<Ctor>, 0);
		RawSetField(m_pScriptLua->GetState(), -2, "__call");

		return *this;
	}

	// Read-Only property
	template <class Get>
	Class& Property(const std::string& iName, Get iGet)
	{
		_GetProperty(iName, iGet);
		return *this;
	}

	template <class Get, class Set>
	Class& Property(const std::string& iName, Get iGet, Set iSet)
	{
		_GetProperty(iName, iGet);

		if (iSet != 0)
		{
			lua_State* L = m_pScriptLua->GetState();
			RawGetField(L, -1, "__propSetter");
			new (lua_newuserdata(L, sizeof(Set))) Set(iSet);
			lua_pushcclosure(L, &CallMember<Set>::Method, 1);
			RawSetField(L, -2, iName.c_str());
			lua_pop(L, 1);
		}
		return *this;
	}

	template <class MethPtr>
	Class& Method(const std::string& iName, MethPtr iMethod)
	{
		new (lua_newuserdata(m_pScriptLua->GetState(), sizeof(MethPtr))) MethPtr(iMethod);
		lua_pushcclosure(m_pScriptLua->GetState(), &CallMember<MethPtr>::Method, 1);
		RawSetField(m_pScriptLua->GetState(), -2, iName.c_str());
		return *this;
	}

protected:
	bool _Initialize()
	{
		lua_State* L = m_pScriptLua->GetState();

		// TODO Verification for lua_istable

		RawGetField(L, -1, m_Name.c_str());

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);

			_CreateClassTable();

			lua_pushvalue(L, -1);
			lua_rawsetp(L, LUA_REGISTRYINDEX, Class<T>::GetIdentityKey());
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

private:
	ScriptLua*        m_pScriptLua;
	const std::string m_Name;

	void _CreateClassTable()
	{
		lua_State* L = m_pScriptLua->GetState();

		// Create the metatable.
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
		lua_pushcfunction(L, &Class::_IndexMetaMethod);
		RawSetField(L, -2, "__index");
		// set __newindex=newIndexMetatable() // indexing assignement metamethod
		lua_pushcfunction(L, &Class::_NewIndexMetaMethod);
		RawSetField(L, -2, "__newindex");
		// set __propGetter=NewLuaTable
		lua_newtable(L);
		RawSetField(L, -2, "__propGetter");
		// set __propSetter=NewLuaTable
		lua_newtable(L);
		RawSetField(L, -2, "__propSetter");

	}

	template <class Get>
	void _GetProperty(const std::string& iName, Get iGet)
	{
		lua_State* L = m_pScriptLua->GetState();
		RawGetField(L, -1, "__propGetter");
		new (lua_newuserdata(L, sizeof(Get))) Get(iGet);
		lua_pushcclosure(L, &CallMember<Get>::Method, 1);
		RawSetField(L, -2, iName.c_str());
		lua_pop(L, 1);
	}

	// constructor proxy method
	template <class Ctor>
	static int _ConstructorProxy(lua_State* iL)
	{
		ArgList<typename ConstructorInvoker<T, Ctor>::Arguments, 2> arguments(iL);
		ConstructorInvoker<T, Ctor>::Call(FullUserData<T>::Construct(iL), arguments);
		return 1;
	}

	// destructor proxy method
	// template<class T>

	// index access metamethod t[k]
	static int _IndexMetaMethod(lua_State* iL)
	{
		int result = 0;

		lua_getmetatable(iL, 1);

		while (true)
		{
			lua_pushvalue(iL, 2);
			lua_rawget(iL, -2);

			if (lua_iscfunction(iL, -1))
			{
				lua_remove(iL, -2);
				result = 1;
				break;
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

			RawGetField(iL, -1, "__propGetter");
			if (lua_istable(iL, -1))
			{
				lua_pushvalue(iL, 2);
				lua_rawget(iL, -2);
				lua_remove(iL, -2);
				if (lua_iscfunction(iL, -1))
				{
					lua_remove(iL, -2);
					lua_pushvalue(iL, 1);
					lua_call(iL, 1, 1);
					result = 1;
					break;
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

			// Simply repeat the lookup in the __parent metafield
			RawGetField(iL, -1, "__parent");
			if (lua_istable(iL, -1))
			{
				// Remove the metatable and repeat the search for the parent
				lua_remove(iL, -2);
			}
			else if (lua_isnil(iL, -1))
			{
				result = 1;
				break;
			}
			else
			{
				lua_pop(iL, 2);
				// TODO throw an exception here
			}
		}

		return result;
	}

	// index assignement metamethod t[k]=v
	static int _NewIndexMetaMethod(lua_State* iL)
	{
		int result = 0;

		lua_getmetatable(iL, 1);

		while (true)
		{
			RawGetField(iL, -1, "__propSetter");

			if (!lua_isnil(iL, -1))
			{
				lua_pushvalue(iL, 2);
				lua_rawget(iL, -2);
			
				if (!lua_isnil(iL, -1))
				{
					lua_pushvalue(iL, 1);
					lua_pushvalue(iL, 3);
					lua_call(iL, 2, 0);
					result = 0;
					break;
				}

				lua_pop(iL, 1);
			}

			lua_pop(iL, 1);

			// Repeat the lookup in the __parent metafield.
			RawGetField(iL, -1, "__parent");
			if (lua_isnil(iL, -1))
			{
				result = luaL_error(iL,
					"No member named '%s'", lua_tostring(iL, 2));
			}
			lua_remove(iL, -2);
		}

		return result;
	}
};

} // namespace CppLua

#endif // !CPPLUA_CLASS_H_
