#ifndef CPPLUA_CLASS_H
#define CPPLUA_CLASS_H

#include "scriptlua.h"
#include "helpers/luahelper.h"
#include "utilities/constructorinvoker.h"
#include "utilities/methodinvoker.h"
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
class FullUserData
{
public:
	static void* Construct(lua_State* iL)
	{
		const FullUserData<T>* userData = 
			new (lua_newuserdata(iL, sizeof(FullUserData<T>))) FullUserData<T>();
		return userData->GetMemoryPtr();
	}

	void* GetMemoryPtr() const
	{
		return m_Ptr;
	}

private:
	FullUserData(const FullUserData<T>&);
	FullUserData<T> operator=(const FullUserData<T>&);

	FullUserData()
	{
		m_Ptr = &m_Memory[0];
	}

	~FullUserData()
	{
		reinterpret_cast<T*>(m_Ptr)->~T();
	}

	char  m_Memory[sizeof(T)];
	void* m_Ptr;
};

template <class T>
class Class
{
public:
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

	template <class Get, class Set>
	Class& Property(const std::string& iName, Get iGet, Set iSet)
	{
		return *this;
	}

	template <class MethPtr>
	Class& Method(const std::string& iName, MethPtr iMethod)
	{
		return *this;
	}

protected:
	bool _Initialize()
	{
		lua_State* L = m_pScriptLua->GetState();

		RawGetField(L, -1, m_Name.c_str());

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);

			_CreateClassTable();
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
		lua_pushvalue(L, -1);
		lua_setmetatable(L, -2);

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

#endif // !CPPLUA_CLASS_H
