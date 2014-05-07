#ifndef CPPLUA_SCRIPTLUA_H
#define CPPLUA_SCRIPTLUA_H

#include <interfaces/iscriptsystem.h>
#include <cpplualib.h>

extern "C"
{
	#include <lua.h>
}

namespace CppLua
{
	
class CPPLUA_API ScriptLua : public IScriptSystem
{
public:
	ScriptLua();
	~ScriptLua();

	bool ExecuteFile( const char* iFileName );
	bool ExecuteBuffer( const char* iBuffer );

private:
	lua_State*    m_pState;

	// Methods
	bool _Initialize();
	bool _Destroy();
};

} // namespace CppLua

#endif // !CPPLUA_SCRIPTLUA_H

