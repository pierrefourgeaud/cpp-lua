
#include <scriptlua.h>

int main()
{
	CppLua::ScriptLua lua;
	lua.ExecuteBuffer("print(\"message\")");
	return 0;
}
