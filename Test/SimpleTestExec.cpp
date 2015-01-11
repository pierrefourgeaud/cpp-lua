
#include <scriptlua.h>

using namespace CppLua;

int main()
{
	ScriptLua lua;

	lua.ExecuteBuffer(
		"print(\"message\")"
		"local num = 3 + 4"
		"print(num)"
		);
}