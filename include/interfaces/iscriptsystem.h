#ifndef CPPLUA_INTERFACES_ISCRIPTSYSTEM_H
#define CPPLUA_INTERFACES_ISCRIPTSYSTEM_H

#include "../cpplualib.h"

namespace CppLua
{

// Interface
class CPPLUA_API IScriptSystem
{
public:
	virtual ~IScriptSystem() {}

	virtual bool ExecuteFile( const char* iFileName ) = 0;
	virtual bool ExecuteBuffer( const char* iBuffer ) = 0;

	// BeginCall
	// PushParam
	// EndCall
};

} // namespace CppLua

#endif // !CPPLUA_INTERFACES_ISCRIPTSYSTEM_H
