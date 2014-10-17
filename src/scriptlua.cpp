#include <scriptlua.h>
#include <string.h>
#include <iostream>

extern "C"
{
	#include <lauxlib.h>
	#include <lualib.h>
}

using namespace CppLua;

ScriptLua::ScriptLua()
	: m_pState( NULL )
{
	_Initialize();
}

ScriptLua::~ScriptLua()
{
	_Destroy();
}

bool
ScriptLua::ExecuteFile( const char* iFileName )
{
	int error = luaL_loadfile(m_pState, iFileName) ||
		lua_pcall(m_pState, 0, 0, 0);

	if (error)
	{
		std::cout << lua_tostring(m_pState, -1) << std::endl;
		lua_pop(m_pState, 1);  /* pop error message from the stack */
		return false;
	}

	return true;
}

bool
ScriptLua::ExecuteBuffer( const char* iBuffer )
{
	int error = luaL_loadbuffer(m_pState, iBuffer, strlen(iBuffer), "") ||
		lua_pcall(m_pState, 0, 0, 0);

	if (error)
	{
		std::cout << lua_tostring(m_pState, -1) << std::endl;
		lua_pop(m_pState, 1);  /* pop error message from the stack */
		return false;
	}
	return true;
}

lua_State*
ScriptLua::GetState() const
{
	return m_pState;
}

// Private
bool
ScriptLua::_Initialize()
{
	// Create and initialize the Lua State
	m_pState = luaL_newstate();

	if ( !m_pState )
	{
		// TODO: Exception
		return false;
	}

	// Open the standard libraries
	luaL_openlibs( m_pState );
	return true;
}

bool
ScriptLua::_Destroy()
{
	if ( m_pState )
	{
		lua_close( m_pState );
		m_pState = NULL;
	}
	return true;
}
